Sub TransferirDadosParaEquipes()
    Dim wsEquipes As Worksheet
    Dim DestRowEquipe1 As Long, DestRowEquipe2 As Long, i As Long
    Dim UsoPercent As Double
    
    ' Definir a planilha "Equipes"
    Set wsEquipes = ThisWorkbook.Sheets("Equipes")
    
    ' Definir a linha de destino para Equipe 1
    DestRowEquipe1 = 125
    
    ' Transferir os dados para a Equipe 1
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 1).Value) Then
            wsEquipes.Cells(DestRowEquipe1, 1).Value = wsEquipes.Cells(i, 1).Value ' ID
            wsEquipes.Cells(DestRowEquipe1, 2).Value = wsEquipes.Cells(i, 2).Value ' Nome
            wsEquipes.Cells(DestRowEquipe1, 3).Value = wsEquipes.Cells(i, 3).Value ' Quantidade
            wsEquipes.Cells(DestRowEquipe1, 4).Value = wsEquipes.Cells(i, 4).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 3).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 5).Value / wsEquipes.Cells(i, 3).Value) * 100
                If UsoPercent = 0 Then
                    wsEquipes.Cells(DestRowEquipe1, 5).ClearContents
                Else
                    wsEquipes.Cells(DestRowEquipe1, 5).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(DestRowEquipe1, 5).ClearContents
            End If
            
            DestRowEquipe1 = DestRowEquipe1 + 1
        End If
    Next i
    
    ' Definir a linha de destino para Equipe 2
    DestRowEquipe2 = 125
    
    ' Transferir os dados para a Equipe 2
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 8).Value) Then
            wsEquipes.Cells(DestRowEquipe2, 8).Value = wsEquipes.Cells(i, 8).Value ' ID
            wsEquipes.Cells(DestRowEquipe2, 9).Value = wsEquipes.Cells(i, 9).Value ' Nome
            wsEquipes.Cells(DestRowEquipe2, 10).Value = wsEquipes.Cells(i, 10).Value ' Quantidade
            wsEquipes.Cells(DestRowEquipe2, 11).Value = wsEquipes.Cells(i, 11).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 10).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 12).Value / wsEquipes.Cells(i, 10).Value) * 100
                If UsoPercent = 0 Then
                    wsEquipes.Cells(DestRowEquipe2, 12).ClearContents
                Else
                    wsEquipes.Cells(DestRowEquipe2, 12).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(DestRowEquipe2, 12).ClearContents
            End If
            
            DestRowEquipe2 = DestRowEquipe2 + 1
        End If
    Next i
    
    ' Limpar os dados originais da Equipe 1 e Equipe 2
    'For i = 12 To 112
    '    wsEquipes.Range("A" & i & ":F" & i).ClearContents
    '    wsEquipes.Range("H" & i & ":n" & i).ClearContents
    'Next i

End Sub

