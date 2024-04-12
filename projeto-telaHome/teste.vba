Sub TransferirDadosParaEquipes()
    Dim wsEquipes As Worksheet
    Dim DestRow As Long, i As Long
    Dim UsoPercent As Double
    
    ' Definir a planilha "Equipes"
    Set wsEquipes = ThisWorkbook.Sheets("Equipes")
    
    ' Definir a linha de destino
    DestRow = 125
    
    ' Transferir os dados para a Equipe 1
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 1).Value) Then
            wsEquipes.Cells(DestRow, 1).Value = wsEquipes.Cells(i, 1).Value ' ID
            wsEquipes.Cells(DestRow, 2).Value = wsEquipes.Cells(i, 2).Value ' Nome
            wsEquipes.Cells(DestRow, 3).Value = wsEquipes.Cells(i, 3).Value ' Quantidade
            wsEquipes.Cells(DestRow, 4).Value = wsEquipes.Cells(i, 4).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 3).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 5).Value / wsEquipes.Cells(i, 3).Value)
                If UsoPercent = 0 Then
                    wsEquipes.Cells(DestRow, 5).ClearContents
                Else
                    wsEquipes.Cells(DestRow, 5).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(DestRow, 5).ClearContents
            End If
            
            DestRow = DestRow + 1
        End If
    Next i
    
    ' Transferir os dados para a Equipe 2
    DestRow = 125
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 8).Value) Then
            wsEquipes.Cells(DestRow, 8).Value = wsEquipes.Cells(i, 8).Value ' ID
            wsEquipes.Cells(DestRow, 9).Value = wsEquipes.Cells(i, 9).Value ' Nome
            wsEquipes.Cells(DestRow, 10).Value = wsEquipes.Cells(i, 10).Value ' Quantidade
            wsEquipes.Cells(DestRow, 11).Value = wsEquipes.Cells(i, 11).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 10).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 12).Value / wsEquipes.Cells(i, 10).Value)
                If UsoPercent = 0 Then
                    wsEquipes.Cells(DestRow, 12).ClearContents
                Else
                    wsEquipes.Cells(DestRow, 12).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(DestRow, 12).ClearContents
            End If
            
            DestRow = DestRow + 1
        End If
    Next i
    
    ' Limpar os dados originais da Equipe 1 e Equipe 2
    'For i = 12 To 112
    '    wsEquipes.Range("A" & i & ":F" & i).ClearContents
    '    wsEquipes.Range("H" & i & ":n" & i).ClearContents
    'Next i

End Sub

