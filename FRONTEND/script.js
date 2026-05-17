const app = document.getElementById("app");

app.innerHTML = `
  <section class="terminal" id="terminalView" aria-label="Terminal view">
    <header class="terminal-header">
      <h1 class="terminal-title">os-terminal</h1>
    </header>

    <form class="cmd-form" id="cmdForm" autocomplete="off">
      <label class="prompt" for="cmdInput">
        <span class="user">student</span>@<span class="path" id="promptHostPath">os:/</span>$
      </label>
      <input id="cmdInput" name="cmd" type="text" placeholder="type a command" aria-label="Terminal command" />
      <button class="btn" type="submit">run</button>
    </form>

    <section class="code-panel" aria-label="Secondary code panel">
      <div class="code-panel-head">
        <div class="panel-title" id="panelTitle">file preview</div>
        <button class="btn btn-ghost" id="panelCopyBtn" type="button">copy</button>
      </div>
      <pre class="output secondary" id="panelCode">Use: vi filename</pre>
    </section>

    <section class="terminal-content" aria-label="Command output">
      <pre class="output" id="output">Available: help, ls, cd <dir>, pwd, vi <file>, clear, whoami, Hello</pre>
    </section>
  </section>

  <section class="dashboard hidden" id="dashboardView" aria-label="Dashboard view">
    <div class="dash-shell">
      <header class="dash-header">
        <h2>Experiment Snippets</h2>
        <button class="action-link" id="toTerminal" type="button">back to terminal</button>
      </header>
      <section class="exp-grid" id="expGrid" aria-label="Experiment cards"></section>
    </div>
  </section>
`;

const terminalView = document.getElementById("terminalView");
const dashboardView = document.getElementById("dashboardView");
const toTerminal = document.getElementById("toTerminal");
const cmdForm = document.getElementById("cmdForm");
const cmdInput = document.getElementById("cmdInput");
const output = document.getElementById("output");
const promptHostPath = document.getElementById("promptHostPath");
const panelTitle = document.getElementById("panelTitle");
const panelCode = document.getElementById("panelCode");
const panelCopyBtn = document.getElementById("panelCopyBtn");
const expGrid = document.getElementById("expGrid");

const fsTree = {
  type: "dir",
  children: {
    "13.c": { type: "file", content: "" },
    "7.c": { type: "file", content: "" },
    "a.out": { type: "file", content: "[Binary/unsupported file preview]" },
    EXP11: { type: "dir", children: { "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "best.c": { type: "file", content: "" }, "first.c": { type: "file", content: "" }, "worst.c": { type: "file", content: "" } } },
    EXP12: { type: "dir", children: { "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "FIFO.c": { type: "file", content: "" }, "LRU.c": { type: "file", content: "" }, "Optimal.c": { type: "file", content: "" } } },
    EXP14: { type: "dir", children: { "14a.c": { type: "file", content: "" }, "14b.c": { type: "file", content: "" }, "14c.c": { type: "file", content: "" }, "a.out": { type: "file", content: "[Binary/unsupported file preview]" } } },
    EXP2: { type: "dir", children: { "2b": { type: "dir", children: { "armstrong.sh": { type: "file", content: "" }, "factorial.sh": { type: "file", content: "" }, "fibo.sh": { type: "file", content: "" }, "greatest_of_three_number.sh": { type: "file", content: "" }, "menu_calc.sh": { type: "file", content: "" }, "prime.sh": { type: "file", content: "" }, "sum_of_two_numbers.sh": { type: "file", content: "" }, "swap_of_two_numbers.sh": { type: "file", content: "" } } }, "2c": { type: "dir", children: { "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "copy.txt": { type: "file", content: "" }, "cp.c": { type: "file", content: "" }, "grep.c": { type: "file", content: "" }, "ls.c": { type: "file", content: "" }, "mov_copy.c": { type: "file", content: "" } } } } },
    EXP3: { type: "dir", children: { "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "fork.c": { type: "file", content: "" }, "getpid.c": { type: "file", content: "" }, "opendir.c": { type: "file", content: "" }, "sleep.c": { type: "file", content: "" }, "stat.c": { type: "file", content: "" }, "wait.c": { type: "file", content: "" } } },
    EXP4: { type: "dir", children: { "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "fcfs.c": { type: "file", content: "" }, "prii_non.c": { type: "file", content: "" }, "prii_pre.c": { type: "file", content: "" }, "pri_pre.c": { type: "file", content: "" }, "rr.c": { type: "file", content: "" }, "sjf.c": { type: "file", content: "" } } },
    EXP5: { type: "dir", children: { "5c.c": { type: "file", content: "" }, "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "5a": { type: "dir", children: { "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "reader.c": { type: "file", content: "" }, "writer.c": { type: "file", content: "" }, "5a_trial": { type: "dir", children: { "reader": { type: "file", content: "[Binary/unsupported file preview]" }, "reader.c": { type: "file", content: "" }, "writer": { type: "file", content: "[Binary/unsupported file preview]" }, "writer.c": { type: "file", content: "" }, "5b": { type: "dir", children: { "a.out": { type: "file", content: "[Binary/unsupported file preview]" }, "rec.c": { type: "file", content: "" }, "sender.c": { type: "file", content: "" } } } } }, "5b": { type: "dir", children: { ".rec.c.swo": { type: "file", content: "[Binary/unsupported file preview]" }, "progfile": { type: "file", content: "[Binary/unsupported file preview]" }, "rec": { type: "file", content: "[Binary/unsupported file preview]" }, "rec.c": { type: "file", content: "" }, "sender": { type: "file", content: "[Binary/unsupported file preview]" }, "sender.c": { type: "file", content: "" } } } } } } }
  }
};

const textExt = new Set([".c", ".h", ".cpp", ".sh", ".txt", ".md", ".js", ".css", ".html", ".json", ".yml", ".yaml", ".py"]);
let cwd = [];
let panelCurrentContent = "";
let dashboardPath = [];

function getNode(pathParts) {
  let node = fsTree;
  for (const part of pathParts) {
    if (!node.children || !node.children[part]) return null;
    node = node.children[part];
  }
  return node;
}

function renderPrompt() {
  const path = cwd.length ? `/${cwd.join("/")}` : "/";
  promptHostPath.textContent = `os:${path}`;
}

function showDashboard() {
  dashboardPath = [];
  populateDashboard();
  terminalView.classList.add("hidden");
  dashboardView.classList.remove("hidden");
}

function showTerminal() {
  dashboardView.classList.add("hidden");
  terminalView.classList.remove("hidden");
  cmdInput.focus();
}

function setOutput(text, className = "") {
  output.className = className ? `output ${className}` : "output";
  output.textContent = text;
}

function resolvePath(inputPath) {
  const isAbsolute = inputPath.startsWith("/");
  const base = isAbsolute ? [] : [...cwd];
  const parts = inputPath.split("/").filter(Boolean);
  for (const part of parts) {
    if (part === ".") continue;
    if (part === "..") base.pop();
    else base.push(part);
  }
  return base;
}

function extOf(name) {
  const i = name.lastIndexOf(".");
  return i >= 0 ? name.slice(i).toLowerCase() : "";
}

async function loadContent(pathParts, fileName) {
  const ext = extOf(fileName);
  if (!textExt.has(ext)) return "[Binary/unsupported file preview]";
  const rel = `../${[...pathParts, fileName].join("/")}`;
  try {
    const res = await fetch(rel);
    if (!res.ok) return "[Unable to load file content]";
    return await res.text();
  } catch {
    return "[Unable to load file content. Run with local server/GitHub Pages.]";
  }
}

async function openFile(pathParts, fileName) {
  const node = getNode([...pathParts, fileName]);
  if (!node || node.type !== "file") return setOutput(`vi: cannot open '${fileName}'`, "error");
  const content = node.content && node.content !== "" ? node.content : await loadContent(pathParts, fileName);
  node.content = content;
  panelTitle.textContent = `${pathParts.length ? `/${pathParts.join("/")}` : "/"}${pathParts.length ? "/" : ""}${fileName}`;
  panelCode.textContent = content;
  panelCurrentContent = content;
  panelCopyBtn.classList.remove("hidden");
  setOutput(content);
}

function walkTextFiles(node, path = [], out = []) {
  if (node.type === "file") {
    const name = path[path.length - 1] || "";
    if (textExt.has(extOf(name))) out.push(path);
    return out;
  }
  for (const [name, child] of Object.entries(node.children || {})) walkTextFiles(child, [...path, name], out);
  return out;
}

async function populateDashboard() {
  expGrid.innerHTML = "";
  const current = getNode(dashboardPath);
  if (!current || current.type !== "dir") return;

  const entries = Object.entries(current.children || {}).sort(([a], [b]) => a.localeCompare(b));
  const header = document.querySelector(".dash-header h2");
  const pathLabel = dashboardPath.length ? `/${dashboardPath.join("/")}` : "/";
  header.textContent = `Explorer ${pathLabel}`;

  if (dashboardPath.length) {
    const upCard = document.createElement("article");
    upCard.className = "card";
    upCard.innerHTML = `<div class="card-head"><span class="file">..</span><button class="copy-btn" type="button">Open</button></div><pre class="code">Go to parent folder</pre>`;
    upCard.querySelector(".copy-btn").addEventListener("click", () => {
      dashboardPath.pop();
      populateDashboard();
    });
    expGrid.appendChild(upCard);
  }

  for (const [name, node] of entries) {
    const card = document.createElement("article");
    card.className = "card";
    const isDir = node.type === "dir";
    const actionLabel = isDir ? "Open" : "Copy";
    const preview = isDir ? "Folder" : "File";
    card.innerHTML = `<div class="card-head"><span class="file">${name}</span><button class="copy-btn" type="button">${actionLabel}</button></div><pre class="code">${preview}</pre>`;

    const actionBtn = card.querySelector(".copy-btn");
    const codeEl = card.querySelector(".code");

    if (isDir) {
      const openDir = () => {
        dashboardPath.push(name);
        populateDashboard();
      };
      actionBtn.addEventListener("click", openDir);
      codeEl.addEventListener("click", openDir);
    } else {
      const parent = [...dashboardPath];
      const fullPath = [...dashboardPath, name];
      if (!node.content) node.content = await loadContent(parent, name);
      codeEl.textContent = node.content || "";

      codeEl.addEventListener("click", () => {
        showTerminal();
        cwd = parent;
        renderPrompt();
        openFile(parent, name);
      });

      actionBtn.addEventListener("click", async () => {
        try {
          await navigator.clipboard.writeText(node.content || "");
          actionBtn.textContent = "Copied";
        } catch {
          actionBtn.textContent = "Failed";
        }
        setTimeout(() => { actionBtn.textContent = "Copy"; }, 900);
      });
      card.querySelector(".file").textContent = fullPath.join("/");
    }

    expGrid.appendChild(card);
  }
}

function runCommand(raw) {
  const cmd = raw.trim();
  const normalized = cmd.toLowerCase();
  if (!cmd) return;
  if (normalized === "hello" || normalized === "dashboard") {
    window.location.href = "dashboard.html";
    return;
  }
  if (cmd === "help") return setOutput("help, ls, cd <dir>, pwd, vi <file>, clear, whoami, Hello");
  if (cmd === "ls") {
    const node = getNode(cwd);
    const names = Object.keys(node.children || {});
    return setOutput(names.length ? names.join("  ") : "(empty)");
  }
  if (cmd === "pwd") return setOutput(cwd.length ? `/${cwd.join("/")}` : "/");
  if (cmd === "whoami") return setOutput("student");
  if (cmd === "clear") return setOutput("");

  if (cmd.startsWith("cd")) {
    const parts = cmd.split(/\s+/);
    if (parts.length === 1 || parts[1] === "~" || parts[1] === "/") {
      cwd = [];
      renderPrompt();
      return setOutput("/");
    }
    const target = resolvePath(parts[1]);
    const node = getNode(target);
    if (!node || node.type !== "dir") return setOutput(`cd: no such file or directory: ${parts[1]}`, "error");
    cwd = target;
    renderPrompt();
    return setOutput(cwd.length ? `/${cwd.join("/")}` : "/");
  }

  if (cmd.startsWith("vi")) {
    const parts = cmd.split(/\s+/);
    if (parts.length < 2) return setOutput("vi: missing file operand", "error");
    const target = parts.slice(1).join(" ");
    const full = resolvePath(target);
    const fileName = full.pop();
    const parent = getNode(full);
    if (!parent || parent.type !== "dir") return setOutput(`vi: cannot open '${target}'`, "error");
    return openFile(full, fileName);
  }

  return setOutput(`-bash: ${cmd}: command not found`, "error");
}

toTerminal.addEventListener("click", showTerminal);
panelCopyBtn.addEventListener("click", async () => {
  try {
    await navigator.clipboard.writeText(panelCurrentContent);
    panelCopyBtn.textContent = "copied";
  } catch {
    panelCopyBtn.textContent = "failed";
  }
  setTimeout(() => { panelCopyBtn.textContent = "copy"; }, 900);
});

cmdForm.addEventListener("submit", (event) => {
  event.preventDefault();
  runCommand(cmdInput.value);
  cmdInput.value = "";
});

renderPrompt();
cmdInput.focus();
