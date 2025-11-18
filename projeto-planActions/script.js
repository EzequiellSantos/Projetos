alert("Script carregado com sucesso!");

google.charts.load("current", { packages: ["timeline"] });
google.charts.setOnLoadCallback(loadData);

async function loadData() {
    const response = await fetch("./dados.csv");
    const text = await response.text();

    console.log("Dados CSV carregados:", text);

    const rows = text
        .trim()
        .split("\n")
        .slice(1) // remove header
        .map(line => {
            const [id, nome, resp, inicio, fim, status, categoria, prioridade] = line.split(";");
            return {
                nome,
                resp,
                inicio: parseDateBR(inicio),
                fim: parseDateBR(fim),
                status,
                categoria,
                prioridade
            };
        });

    drawTimeline(rows);
}

function parseDateBR(dateStr) {
    const [dia, mes, ano] = dateStr.split("/");
    return new Date(`${ano}-${mes}-${dia}`);
}

function drawTimeline(data) {
    const container = document.getElementById("timeline");
    const chart = new google.visualization.Timeline(container);
    const chartData = new google.visualization.DataTable();

    chartData.addColumn({ type: 'string', id: 'Responsavel' });
    chartData.addColumn({ type: 'string', id: 'Projeto' });
    chartData.addColumn({ type: 'date', id: 'Start' });
    chartData.addColumn({ type: 'date', id: 'End' });

    data.forEach(p => {
        chartData.addRow([p.resp, `${p.nome} (${p.status})`, p.inicio, p.fim]);
    });

    chart.draw(chartData, {
        timeline: { showRowLabels: true },
        height: data.length * 60,
    });
}
