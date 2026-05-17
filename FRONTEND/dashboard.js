const expGrid = document.getElementById('expGrid');
const viewer = document.getElementById('viewer');
const note = document.getElementById('note');
const mainTitle = document.getElementById('mainTitle');
const mainCode = document.getElementById('mainCode');
const mainCopyBtn = document.getElementById('mainCopyBtn');
const pkgCard = document.getElementById('pkgCard');
const pkgCode = document.getElementById('pkgCode');
const pkgCopyBtn = document.getElementById('pkgCopyBtn');

let currentMainCode = '';
let currentPkgCode = '';
let currentPath = [];

const fsTree = {
  type: 'dir',
  children: {
    '13.c': { type: 'file' }, '7.c': { type: 'file' }, 'a.out': { type: 'file', binary: true },
    'EXP11': { type: 'dir', children: { 'a.out': { type: 'file', binary: true }, 'best.c': { type: 'file' }, 'first.c': { type: 'file' }, 'worst.c': { type: 'file' } } },
    'EXP12': { type: 'dir', children: { 'a.out': { type: 'file', binary: true }, 'FIFO.c': { type: 'file' }, 'LRU.c': { type: 'file' }, 'Optimal.c': { type: 'file' } } },
    'EXP14': { type: 'dir', children: { '14a.c': { type: 'file' }, '14b.c': { type: 'file' }, '14c.c': { type: 'file' }, 'a.out': { type: 'file', binary: true } } },
    'EXP2': { type: 'dir', children: { '2b': { type: 'dir', children: { 'armstrong.sh': { type: 'file' }, 'factorial.sh': { type: 'file' }, 'fibo.sh': { type: 'file' }, 'greatest_of_three_number.sh': { type: 'file' }, 'menu_calc.sh': { type: 'file' }, 'prime.sh': { type: 'file' }, 'sum_of_two_numbers.sh': { type: 'file' }, 'swap_of_two_numbers.sh': { type: 'file' } } }, '2c': { type: 'dir', children: { 'a.out': { type: 'file', binary: true }, 'copy.txt': { type: 'file' }, 'cp.c': { type: 'file' }, 'grep.c': { type: 'file' }, 'ls.c': { type: 'file' }, 'mov_copy.c': { type: 'file' } } } } },
    'EXP3': { type: 'dir', children: { 'a.out': { type: 'file', binary: true }, 'fork.c': { type: 'file' }, 'getpid.c': { type: 'file' }, 'opendir.c': { type: 'file' }, 'sleep.c': { type: 'file' }, 'stat.c': { type: 'file' }, 'wait.c': { type: 'file' } } },
    'EXP4': { type: 'dir', children: { 'a.out': { type: 'file', binary: true }, 'fcfs.c': { type: 'file' }, 'prii_non.c': { type: 'file' }, 'prii_pre.c': { type: 'file' }, 'pri_pre.c': { type: 'file' }, 'rr.c': { type: 'file' }, 'sjf.c': { type: 'file' } } },
    'EXP5': { type: 'dir', children: { '5c.c': { type: 'file' }, 'a.out': { type: 'file', binary: true }, '5a': { type: 'dir', children: { 'a.out': { type: 'file', binary: true }, 'reader.c': { type: 'file' }, 'writer.c': { type: 'file' }, '5a_trial': { type: 'dir', children: { 'reader': { type: 'file', binary: true }, 'reader.c': { type: 'file' }, 'writer': { type: 'file', binary: true }, 'writer.c': { type: 'file' }, '5b': { type: 'dir', children: { 'a.out': { type: 'file', binary: true }, 'rec.c': { type: 'file' }, 'sender.c': { type: 'file' } } } } }, '5b': { type: 'dir', children: { '.rec.c.swo': { type: 'file', binary: true }, 'progfile': { type: 'file', binary: true }, 'rec': { type: 'file', binary: true }, 'rec.c': { type: 'file' }, 'sender': { type: 'file', binary: true }, 'sender.c': { type: 'file' } } } } } } }
  }
};

function getNode(parts) {
  let node = fsTree;
  for (const p of parts) {
    if (!node.children || !node.children[p]) return null;
    node = node.children[p];
  }
  return node;
}

async function loadCode(parts) {
  const name = parts[parts.length - 1] || '';
  if (!name.includes('.') || name.endsWith('.out')) return '[Binary/unsupported file preview]';
  const res = await fetch(`../${parts.join('/')}`, { cache: 'no-store' });
  if (!res.ok) throw new Error(`Could not load ${parts.join('/')}`);
  return res.text();
}

async function renderGrid() {
  expGrid.innerHTML = '';
  const node = getNode(currentPath);
  if (!node || node.type !== 'dir') return;

  if (currentPath.length) {
    const up = document.createElement('button');
    up.type = 'button';
    up.className = 'exp-btn';
    up.textContent = '..';
    up.addEventListener('click', () => {
      currentPath.pop();
      viewer.classList.add('hidden');
      renderGrid();
      note.textContent = `Path: /${currentPath.join('/')}`;
    });
    expGrid.appendChild(up);
  }

  const names = Object.keys(node.children || {}).sort();
  for (const name of names) {
    const child = node.children[name];
    const btn = document.createElement('button');
    btn.type = 'button';
    btn.className = 'exp-btn';
    btn.textContent = child.type === 'dir' ? `${name}/` : name;
    btn.addEventListener('click', async () => {
      if (child.type === 'dir') {
        currentPath.push(name);
        viewer.classList.add('hidden');
        await renderGrid();
        note.textContent = `Path: /${currentPath.join('/')}`;
        return;
      }
      await openFile(name);
    });
    expGrid.appendChild(btn);
  }
}

async function openFile(name) {
  try {
    viewer.classList.remove('hidden');
    const full = [...currentPath, name];
    const node = getNode(full);
    mainTitle.textContent = full.join('/');
    currentMainCode = node.binary ? '[Binary/unsupported file preview]' : await loadCode(full);
    mainCode.textContent = currentMainCode;

    const dir = getNode(currentPath);
    const siblings = Object.keys(dir.children || {}).sort().join('\n');
    currentPkgCode = siblings;
    pkgCode.textContent = currentPkgCode;
    pkgCard.classList.remove('hidden');

    note.textContent = `Showing ${name}`;
  } catch (err) {
    note.textContent = err.message;
  }
}

mainCopyBtn.addEventListener('click', async () => {
  if (!currentMainCode) return;
  await navigator.clipboard.writeText(currentMainCode);
});

pkgCopyBtn.addEventListener('click', async () => {
  if (!currentPkgCode) return;
  await navigator.clipboard.writeText(currentPkgCode);
});

(async function init() {
  note.textContent = 'Select a folder/file box to view code.';
  await renderGrid();
})();
