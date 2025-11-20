// ============================
// LEITURA DO CSV
// ============================


async function loadData() {
    const response = await fetch("./dados.csv");
    const text = await response.text();

    console.log("CSV carregado:", text);

    const rows = text
        .trim()
        .split("\n")
        .slice(1) // remove header
        .map(line => {
            const [id, nome, resp, inicio, fim, status, categoria, prioridade] = line.split(";");

            return {
                id,
                nome,
                resp,
                inicio: parseDateBR(inicio),
                fim: parseDateBR(fim),
                status,
                categoria,
                prioridade
            };
        });

    createGantt(rows);
}


// ============================
// CONVERSÃO DE DATA BR
// ============================

function parseDateBR(dateStr) {
    const [dia, mes, ano] = dateStr.trim().split("/");
    return `${ano}-${mes}-${dia}`;
    // Frappe Gantt aceita string yyyy-mm-dd 👍
}


// ============================
// CRIAÇÃO DO GANTT (FRAPPE GANTT)
// ============================

function createGantt(data) {

    // Converter seus dados em tarefas do Frappe Gantt
    const tasks = data.map((p, index) => ({
        id: `task-${index}`,
        name: `${p.nome} (${p.status})`,
        start: p.inicio,
        end: p.fim,
        progress: getProgressByStatus(p.status),
        custom_class: getClassByStatus(p.status)
    }));

    console.log("Tasks para o Frappe Gantt:", tasks);

    new Gantt("#gantt", tasks, {
        view_mode: "Month",
        bar_height: 25,
        padding: 18,
        bar_corner_radius: 7,
        custom_popup_html: task => {
            return `
                <div class="details-popup">
                    <h4>${task.name}</h4>
                    <p><strong>Início:</strong> ${task.start}</p>
                    <p><strong>Fim:</strong> ${task.end}</p>
                </div>
            `;
        }
    });
}


// ============================
// DEFINIR CORES POR STATUS
// ============================

function getClassByStatus(status) {
    status = status.toLowerCase();

    if (status.includes("concl")) return "task-status-concluido";
    if (status.includes("andamento")) return "task-status-andamento";
    if (status.includes("planejado")) return "task-status-planejado";
    if (status.includes("risco")) return "task-status-risco";
    if (status.includes("atrasado")) return "task-status-atrasado";

    return "task-status-outros";
}

// Progresso visual opcional
function getProgressByStatus(status) {
    status = status.toLowerCase();
    if (status.includes("concl")) return 100;
    if (status.includes("andamento")) return 50;
    return 20;
}


// ============================
// INICIAR
// ============================

loadData();
