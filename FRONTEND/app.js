import { fsTree } from './fs-tree.js';

const cmdForm = document.getElementById('cmdForm');
const cmdInput = document.getElementById('cmdInput');
const codeView = document.getElementById('codeView');
const fileName = document.getElementById('fileName');
const copyBtn = document.getElementById('copyBtn');
const relatedWrap = document.getElementById('relatedWrap');
const relatedCode = document.getElementById('relatedCode');
const promptPath = document.getElementById('promptPath');

let currentCode = '';
let cwd = [];

function pathToString(parts) {
  return parts.length ? `/${parts.join('/')}` : '/';
}

function setPrompt() {
  promptPath.textContent = `:${pathToString(cwd)}$`;
}

function getNode(parts) {
  let node = fsTree;
  for (const p of parts) {
    if (!node.children || !node.children[p]) return null;
    node = node.children[p];
  }
  return node;
}

function resolvePath(input) {
  const base = input.startsWith('/') ? [] : [...cwd];
  for (const part of input.split('/').filter(Boolean)) {
    if (part === '.') continue;
    if (part === '..') base.pop();
    else base.push(part);
  }
  return base;
}

function renderCode(label, code) {
  fileName.textContent = label;
  codeView.textContent = code;
  currentCode = code;
}

function renderRelated(title, content) {
  if (!content) {
    relatedWrap.classList.add('hidden');
    relatedCode.textContent = '';
    return;
  }
  relatedWrap.classList.remove('hidden');
  relatedWrap.querySelector('.related-title').textContent = title;
  relatedCode.textContent = content;
}

function renderError(message) {
  fileName.textContent = 'Error';
  codeView.innerHTML = `<code class="error">${message}</code>`;
  currentCode = '';
  renderRelated('', '');
}

async function loadCode(parts) {
  const name = parts[parts.length - 1] || '';
  if (!name.includes('.') || name.endsWith('.out')) return '[Binary/unsupported file preview]';
  const rel = `../${parts.join('/')}`;
  const res = await fetch(rel, { cache: 'no-store' });
  if (!res.ok) throw new Error(`Could not load ${parts.join('/')}`);
  return res.text();
}

async function runCommand(raw) {
  const cmd = raw.trim();
  if (!cmd) return;

  if (/^hello$/i.test(cmd)) {
    window.location.assign('./dashboard.html');
    return;
  }

  if (cmd === 'clear') {
    renderCode('Command', '" enter command "');
    renderRelated('', '');
    return;
  }

  if (cmd === ':q') {
    renderCode('Command', 'session closed');
    renderRelated('', '');
    return;
  }

  if (cmd === 'ls') {
    const node = getNode(cwd);
    if (!node || node.type !== 'dir') return renderError('Invalid directory state');
    const names = Object.keys(node.children || {}).sort();
    renderCode(pathToString(cwd), names.join('  ') || '(empty)');
    renderRelated('Directory Listing', names.join('\n'));
    return;
  }

  if (cmd === 'pwd') {
    renderCode('Path', pathToString(cwd));
    renderRelated('', '');
    return;
  }

  const parts = cmd.split(/\s+/);
  if (parts[0] === 'cd') {
    const target = parts[1] || '/';
    const resolved = resolvePath(target === '~' ? '/' : target);
    const node = getNode(resolved);
    if (!node || node.type !== 'dir') return renderError(`cd: no such file or directory: ${target}`);
    cwd = resolved;
    setPrompt();
    renderCode('Path', pathToString(cwd));
    renderRelated('', '');
    return;
  }

  if (parts[0] !== 'vi' || parts.length < 2) {
    return renderError('Use: vi <filename>');
  }

  const target = parts.slice(1).join(' ');
  const full = resolvePath(target);
  const node = getNode(full);
  if (!node || node.type !== 'file') return renderError(`File not found: ${target}`);

  try {
    const code = node.binary ? '[Binary/unsupported file preview]' : await loadCode(full);
    renderCode(full.join('/'), code);
    const parent = full.slice(0, -1);
    const parentNode = getNode(parent);
    if (parentNode && parentNode.type === 'dir') {
      const sib = Object.keys(parentNode.children || {}).sort().join('\n');
      renderRelated('Related Files', sib);
    } else {
      renderRelated('', '');
    }
  } catch (err) {
    renderError(err.message);
  }
}

copyBtn.addEventListener('click', async () => {
  if (!currentCode) return;
  try {
    await navigator.clipboard.writeText(currentCode);
    const t = copyBtn.textContent;
    copyBtn.textContent = 'copied';
    setTimeout(() => { copyBtn.textContent = t; }, 800);
  } catch {
    copyBtn.textContent = 'failed';
    setTimeout(() => { copyBtn.textContent = 'copy'; }, 1000);
  }
});

cmdForm.addEventListener('submit', async (e) => {
  e.preventDefault();
  const raw = cmdInput.value;
  cmdInput.value = '';
  await runCommand(raw);
});

(function init() {
  setPrompt();
  renderCode('Command', 'Type vi EXP11/best.c and press run.');
  cmdInput.focus();
})();






