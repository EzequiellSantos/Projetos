Sub TransferirDados()

    Dim ws As Worksheet
    Dim wsEquipes As Worksheet
    Dim rngEquipes As Range
    Dim rngTabela As Range
    Dim i As Integer
    Dim j As Integer
    Dim ultimaLinha As Long
    Dim porcentagem As Double
    Dim linhaInicial As Integer
    Dim linhaFinal As Integer

    ' Defina a planilha principal "Equipes"
    Set wsEquipes = ThisWorkbook.Sheets("Equipes")

    ' Limpa os dados existentes na linha 124
    wsEquipes.Range("A124:F130").ClearContents

    ' Define a linha inicial para colar os dados
    ultimaLinha = 124

    ' Loop para percorrer cada equipe
    For i = 1 To 6

        ' Define os intervalos de linhas para cada equipe
        linhaInicial = 12 + (i - 1) * 17
        linhaFinal = 112 + (i - 1) * 17

        ' Define a planilha e o range da tabela atual
        Set rngTabela = wsEquipes.Range(wsEquipes.Cells(linhaInicial, 1), wsEquipes.Cells(linhaFinal, 6))

        ' Loop para transferir os dados
        For j = 1 To 6
            wsEquipes.Cells(ultimaLinha, j).Value = rngTabela.Cells(j, 1).Value
        Next j

        ' Calcula e insere a porcentagem de Uso em relação à Quantidade
        porcentagem = (rngTabela.Cells(6, 4).Value + rngTabela.Cells(6, 5).Value) / rngTabela.Cells(3, 3).Value
        wsEquipes.Cells(ultimaLinha, 7).Value = porcentagem & "%"

        ' Atualiza a linha inicial para a próxima equipe
        ultimaLinha = ultimaLinha + 1

    Next i

    MsgBox "Dados transferidos com sucesso!", vbInformation

End Sub