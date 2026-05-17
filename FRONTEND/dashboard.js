import { fsTree } from './fs-tree.js';

const expGrid = document.getElementById('expGrid');
const explorerList = document.getElementById('explorerList');
const viewer = document.getElementById('viewer');
const statusEl = document.getElementById('status');
const breadcrumb = document.getElementById('breadcrumb');
const searchInput = document.getElementById('searchInput');
const themeBtn = document.getElementById('themeBtn');

const mainTitle = document.getElementById('mainTitle');
const fileMeta = document.getElementById('fileMeta');
const mainCode = document.getElementById('mainCode');
const mainCopyBtn = document.getElementById('mainCopyBtn');
const downloadBtn = document.getElementById('downloadBtn');

let currentPath = [];
let currentMainCode = '';
let currentMainFile = '';
let query = '';
let favorites = new Set(JSON.parse(localStorage.getItem('dashboard_favs') || '[]'));

function getNode(parts) {
  let node = fsTree;
  for (const p of parts) {
    if (!node.children || !node.children[p]) return null;
    node = node.children[p];
  }
  return node;
}

function countMeta(dirNode) {
  let files = 0;
  let dirs = 0;
  for (const [, child] of Object.entries(dirNode.children || {})) {
    if (child.type === 'dir') dirs += 1;
    else files += 1;
  }
  return { files, dirs };
}

function pathText(parts) {
  return parts.length ? `/${parts.join('/')}` : '/';
}

function escapeHtml(text) {
  return text
    .replaceAll('&', '&amp;')
    .replaceAll('<', '&lt;')
    .replaceAll('>', '&gt;');
}

function highlightC(code) {
  let html = escapeHtml(code);
  html = html.replace(/(\/\/.*$)/gm, '<span class="tok-com">$1</span>');
  html = html.replace(/(\/\*[\s\S]*?\*\/)/g, '<span class="tok-com">$1</span>');
  html = html.replace(/("([^"\\]|\\.)*")/g, '<span class="tok-str">$1</span>');
  html = html.replace(/\b(\d+(?:\.\d+)?)\b/g, '<span class="tok-num">$1</span>');
  html = html.replace(/(^\s*#\s*\w+)/gm, '<span class="tok-pre">$1</span>');
  html = html.replace(/\b(int|char|float|double|void|long|short|unsigned|signed|const|static|struct|return|if|else|for|while|switch|case|break|continue|typedef|include)\b/g, '<span class="tok-key">$1</span>');
  html = html.replace(/\b(size_t|FILE|pid_t)\b/g, '<span class="tok-type">$1</span>');
  return html;
}

function withLineNumbers(codeHtml) {
  const lines = codeHtml.split('\n');
  const rows = lines.map((line, i) => `<tr><td class="ln">${i + 1}</td><td class="lc">${line || ' '}</td></tr>`).join('');
  return `<table class="code-table"><tbody>${rows}</tbody></table>`;
}

async function loadCode(parts) {
  const name = parts[parts.length - 1] || '';
  if (!name.includes('.') || name.endsWith('.out')) return '[Binary/unsupported file preview]';
  const res = await fetch(`../${parts.join('/')}`, { cache: 'no-store' });
  if (!res.ok) throw new Error(`Could not load ${parts.join('/')}`);
  return res.text();
}

function persistFavs() {
  localStorage.setItem('dashboard_favs', JSON.stringify(Array.from(favorites)));
}

function renderBreadcrumb() {
  breadcrumb.innerHTML = '';
  const crumbs = ['Home', ...currentPath];
  crumbs.forEach((label, idx) => {
    if (idx > 0) {
      const sep = document.createElement('span');
      sep.className = 'sep';
      sep.textContent = '>';
      breadcrumb.appendChild(sep);
    }
    const btn = document.createElement('button');
    btn.className = `crumb ${idx === crumbs.length - 1 ? 'active' : ''}`;
    btn.type = 'button';
    btn.textContent = label;
    btn.addEventListener('click', () => {
      currentPath = idx === 0 ? [] : currentPath.slice(0, idx);
      viewer.classList.add('hidden');
      render();
    });
    breadcrumb.appendChild(btn);
  });
}

function renderExperiments(rootNode) {
  expGrid.innerHTML = '';
  const entries = Object.entries(rootNode.children || {})
    .map(([name, node]) => ({ name, node }))
    .filter((x) => {
      const n = x.name.toLowerCase();
      const isDir = x.node.type === 'dir';
      const isCFile = x.node.type === 'file' && n.endsWith('.c');
      return (isDir || isCFile) && n.includes(query);
    })
    .sort((a, b) => {
      if (a.node.type !== b.node.type) return a.node.type === 'dir' ? -1 : 1;
      return a.name.localeCompare(b.name);
    });

  if (!entries.length) {
    statusEl.textContent = 'No experiments match your search.';
    return;
  }

  const folderCount = entries.filter((e) => e.node.type === 'dir').length;
  const fileCount = entries.length - folderCount;
  statusEl.textContent = `${folderCount} folders • ${fileCount} files`;

  entries.forEach(({ name, node }) => {
    const key = name;
    const card = document.createElement('article');
    card.className = 'exp-card';
    const isDir = node.type === 'dir';
    const meta = isDir ? countMeta(node) : { files: 1, dirs: 0 };
    const icon = isDir ? '📁' : '📄';
    const metaText = isDir ? `${meta.files} files • ${meta.dirs} folders` : 'File';
    card.innerHTML = `
      <div class="exp-head">
        <span class="icon">${icon}</span>
        <button class="star ${favorites.has(key) ? 'active' : ''}" type="button" title="Favorite">★</button>
      </div>
      <h3 class="exp-title">${name}</h3>
      <div class="meta">${metaText}</div>
    `;

    card.addEventListener('click', () => {
      if (isDir) {
        currentPath = [name];
        viewer.classList.add('hidden');
        render();
      } else {
        openFile(name, node);
      }
    });

    card.querySelector('.star').addEventListener('click', (e) => {
      e.stopPropagation();
      if (favorites.has(key)) favorites.delete(key);
      else favorites.add(key);
      persistFavs();
      render();
    });

    expGrid.appendChild(card);
  });
}

function renderExplorer(node) {
  explorerList.innerHTML = '';

  let entries = Object.entries(node.children || {}).map(([name, value]) => ({ name, value }));
  entries = entries
    .filter((e) => e.name.toLowerCase().includes(query))
    .sort((a, b) => {
      if (a.value.type !== b.value.type) return a.value.type === 'dir' ? -1 : 1;
      return a.name.localeCompare(b.name);
    });

  if (!entries.length) {
    statusEl.textContent = 'No items found in this folder.';
    return;
  }

  const meta = countMeta(node);
  statusEl.textContent = `${pathText(currentPath)} • ${meta.files} files • ${meta.dirs} folders`;

  if (currentPath.length) {
    const up = document.createElement('article');
    up.className = 'item';
    up.innerHTML = `<span>↩</span><div><div class="name">..</div><div class="hint">Go to parent folder</div></div><span></span>`;
    up.addEventListener('click', () => {
      currentPath.pop();
      viewer.classList.add('hidden');
      render();
    });
    explorerList.appendChild(up);
  }

  entries.forEach(({ name, value }) => {
    const row = document.createElement('article');
    const icon = value.type === 'dir' ? '📁' : '📄';
    row.className = 'item';
    row.innerHTML = `<span>${icon}</span><div><div class="name">${name}${value.type === 'dir' ? '/' : ''}</div><div class="hint">${value.type === 'dir' ? 'Folder' : 'File'}</div></div><span class="hint">open</span>`;

    row.addEventListener('click', async () => {
      if (value.type === 'dir') {
        currentPath.push(name);
        viewer.classList.add('hidden');
        render();
        return;
      }
      await openFile(name, value);
    });

    explorerList.appendChild(row);
  });
}

async function openFile(name, node) {
  const full = [...currentPath, name];
  currentMainFile = name;
  mainTitle.textContent = full.join('/');
  fileMeta.textContent = 'Loading...';
  mainCode.innerHTML = `<div style="padding:12px"><div class="skeleton"></div><div class="skeleton" style="margin-top:8px"></div><div class="skeleton" style="margin-top:8px"></div></div>`;
  viewer.classList.remove('hidden');

  try {
    const raw = node.binary ? '[Binary/unsupported file preview]' : await loadCode(full);
    currentMainCode = raw;
    const highlighted = name.toLowerCase().endsWith('.c') ? highlightC(raw) : escapeHtml(raw);
    mainCode.innerHTML = withLineNumbers(highlighted);
    fileMeta.textContent = `${raw.split('\n').length} lines`;
    statusEl.textContent = `Opened ${full.join('/')}`;
  } catch (err) {
    currentMainCode = '';
    mainCode.textContent = err.message;
    fileMeta.textContent = 'Error';
    statusEl.textContent = err.message;
  }
}

function render() {
  const rootNode = getNode(currentPath);
  renderBreadcrumb();

  if (!rootNode || rootNode.type !== 'dir') {
    statusEl.textContent = 'Invalid path';
    expGrid.innerHTML = '';
    explorerList.innerHTML = '';
    return;
  }

  if (currentPath.length === 0) {
    explorerList.classList.add('hidden');
    expGrid.classList.remove('hidden');
    renderExperiments(rootNode);
  } else {
    expGrid.classList.add('hidden');
    explorerList.classList.remove('hidden');
    renderExplorer(rootNode);
  }
}

mainCopyBtn.addEventListener('click', async () => {
  if (!currentMainCode) return;
  try {
    await navigator.clipboard.writeText(currentMainCode);
    const t = mainCopyBtn.textContent;
    mainCopyBtn.textContent = 'Copied Successfully';
    setTimeout(() => { mainCopyBtn.textContent = t; }, 1000);
  } catch {
    mainCopyBtn.textContent = 'Copy Failed';
    setTimeout(() => { mainCopyBtn.textContent = 'Copy'; }, 1000);
  }
});

downloadBtn.addEventListener('click', () => {
  if (!currentMainCode || !currentMainFile) return;
  const blob = new Blob([currentMainCode], { type: 'text/plain' });
  const url = URL.createObjectURL(blob);
  const a = document.createElement('a');
  a.href = url;
  a.download = currentMainFile;
  a.click();
  URL.revokeObjectURL(url);
});

searchInput.addEventListener('input', () => {
  query = searchInput.value.trim().toLowerCase();
  render();
});

themeBtn.addEventListener('click', () => {
  const current = document.body.getAttribute('data-theme') || 'dark';
  const next = current === 'dark' ? 'light' : 'dark';
  document.body.setAttribute('data-theme', next);
  localStorage.setItem('dashboard_theme', next);
  themeBtn.textContent = next === 'dark' ? 'light' : 'dark';
});

(function init() {
  const saved = localStorage.getItem('dashboard_theme') || 'dark';
  document.body.setAttribute('data-theme', saved);
  themeBtn.textContent = saved === 'dark' ? 'light' : 'dark';
  statusEl.textContent = 'Ready.';
  render();
})();





