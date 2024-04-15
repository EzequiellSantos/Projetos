Sub TransferirDadosParaEquipes()
    Dim wsEquipes As Worksheet
    Dim i As Long
    Dim UsoPercent As Double
    Dim LastRow As Long
    Dim LastRow1 As Long
    Dim LastRow2 As Long
    Dim LastRow3 As Long
    Dim LastRow4 As Long
    Dim LastRow5 As Long
    Dim LastRow6 As Long
    
    ' Definir a planilha "Equipes"
    Set wsEquipes = ThisWorkbook.Sheets("Equipes")

    
    ' Transferir os dados para a Equipe 1
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 1).Value) Then
            ' Encontrar a última linha na coluna B do intervalo Equipe01
            LastRow1 = wsEquipes.Cells(wsEquipes.Rows.Count, "A").End(xlUp).Row + 1

            wsEquipes.Cells(LastRow1, 1).Value = wsEquipes.Cells(i, 1).Value ' ID
            wsEquipes.Cells(LastRow1, 2).Value = wsEquipes.Cells(i, 2).Value ' Nome
            wsEquipes.Cells(LastRow1, 3).Value = wsEquipes.Cells(i, 3).Value ' Quantidade
            wsEquipes.Cells(LastRow1, 4).Value = wsEquipes.Cells(i, 4).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 3).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 5).Value / wsEquipes.Cells(i, 3).Value) 
                If UsoPercent = 0 Then
                    wsEquipes.Cells(LastRow1, 5).ClearContents
                Else
                    wsEquipes.Cells(LastRow1, 5).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(LastRow1, 5).ClearContents
            End If
            
            LastRow1 = LastRow1 + 1
        End If
    Next i
    
    
    ' Transferir os dados para a Equipe 2
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 9).Value) Then
            ' Encontrar a última linha na coluna B do intervalo Equipe02
            LastRow2 = wsEquipes.Cells(wsEquipes.Rows.Count, "I").End(xlUp).Row + 1

            wsEquipes.Cells(LastRow2, 9).Value = wsEquipes.Cells(i, 9).Value ' ID
            wsEquipes.Cells(LastRow2, 10).Value = wsEquipes.Cells(i, 10).Value ' Nome
            wsEquipes.Cells(LastRow2, 11).Value = wsEquipes.Cells(i, 11).Value ' Quantidade
            wsEquipes.Cells(LastRow2, 12).Value = wsEquipes.Cells(i, 12).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 11).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 13).Value / wsEquipes.Cells(i, 11).Value) 
                If UsoPercent = 0 Then
                    wsEquipes.Cells(LastRow2, 13).ClearContents
                Else
                    wsEquipes.Cells(LastRow2, 13).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(LastRow2, 13).ClearContents
            End If
            
            LastRow2 = LastRow2 + 1
        End If
    Next i

    ' Transferir os dados para a Equipe 3
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 17).Value) Then
            ' Encontrar a última linha na coluna B do intervalo Equipe03
            LastRow3 = wsEquipes.Cells(wsEquipes.Rows.Count, "Q").End(xlUp).Row + 1

            wsEquipes.Cells(LastRow3, 17).Value = wsEquipes.Cells(i, 17).Value ' ID
            wsEquipes.Cells(LastRow3, 18).Value = wsEquipes.Cells(i, 18).Value ' Nome
            wsEquipes.Cells(LastRow3, 19).Value = wsEquipes.Cells(i, 19).Value ' Quantidade
            wsEquipes.Cells(LastRow3, 20).Value = wsEquipes.Cells(i, 20).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 19).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 21).Value / wsEquipes.Cells(i, 19).Value) 
                If UsoPercent = 0 Then
                    wsEquipes.Cells(LastRow3, 21).ClearContents
                Else
                    wsEquipes.Cells(LastRow3, 21).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(LastRow3, 21).ClearContents
            End If
            
            LastRow3 = LastRow3 + 1
        End If
    Next i

    ' Transferir os dados para a Equipe 4
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 25).Value) Then
            ' Encontrar a última linha na coluna B do intervalo Equipe04
            LastRow4 = wsEquipes.Cells(wsEquipes.Rows.Count, "Y").End(xlUp).Row + 1

            wsEquipes.Cells(LastRow4, 25).Value = wsEquipes.Cells(i, 25).Value ' ID
            wsEquipes.Cells(LastRow4, 26).Value = wsEquipes.Cells(i, 26).Value ' Nome
            wsEquipes.Cells(LastRow4, 27).Value = wsEquipes.Cells(i, 27).Value ' Quantidade
            wsEquipes.Cells(LastRow4, 28).Value = wsEquipes.Cells(i, 28).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 27).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 29).Value / wsEquipes.Cells(i, 27).Value) 
                If UsoPercent = 0 Then
                    wsEquipes.Cells(LastRow4, 29).ClearContents
                Else
                    wsEquipes.Cells(LastRow4, 29).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(LastRow4, 29).ClearContents
            End If
            
            LastRow4 = LastRow4 + 1
        End If
    Next i
    
    ' Transferir os dados para a Equipe 5
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 33).Value) Then
            ' Encontrar a última linha na coluna B do intervalo Equipe05
            LastRow5 = wsEquipes.Cells(wsEquipes.Rows.Count, "AG").End(xlUp).Row + 1

            wsEquipes.Cells(LastRow5, 33).Value = wsEquipes.Cells(i, 33).Value ' ID
            wsEquipes.Cells(LastRow5, 34).Value = wsEquipes.Cells(i, 34).Value ' Nome
            wsEquipes.Cells(LastRow5, 35).Value = wsEquipes.Cells(i, 35).Value ' Quantidade
            wsEquipes.Cells(LastRow5, 36).Value = wsEquipes.Cells(i, 36).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 35).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 37).Value / wsEquipes.Cells(i, 35).Value) 
                If UsoPercent = 0 Then
                    wsEquipes.Cells(LastRow5, 37).ClearContents
                Else
                    wsEquipes.Cells(LastRow5, 37).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(LastRow5, 37).ClearContents
            End If
            
            LastRow5 = LastRow5 + 1
        End If
    Next i

    ' Transferir os dados para a Manutençâo
    For i = 12 To 112
        If Not IsEmpty(wsEquipes.Cells(i, 41).Value) Then
            ' Encontrar a última linha na coluna B do intervalo Manutençâo
            LastRow6 = wsEquipes.Cells(wsEquipes.Rows.Count, "AO").End(xlUp).Row + 1

            wsEquipes.Cells(LastRow6, 41).Value = wsEquipes.Cells(i, 41).Value ' ID
            wsEquipes.Cells(LastRow6, 42).Value = wsEquipes.Cells(i, 42).Value ' Nome
            wsEquipes.Cells(LastRow6, 43).Value = wsEquipes.Cells(i, 43).Value ' Quantidade
            wsEquipes.Cells(LastRow6, 44).Value = wsEquipes.Cells(i, 44).Value ' Data
            
            ' Calcular a porcentagem de Uso
            If wsEquipes.Cells(i, 43).Value <> 0 Then
                UsoPercent = (wsEquipes.Cells(i, 45).Value / wsEquipes.Cells(i, 43).Value) 
                If UsoPercent = 0 Then
                    wsEquipes.Cells(LastRow6, 45).ClearContents
                Else
                    wsEquipes.Cells(LastRow6, 45).Value = UsoPercent
                End If
            Else
                wsEquipes.Cells(LastRow6, 45).ClearContents
            End If
            
            LastRow6 = LastRow6 + 1
        End If
    Next i

    'Limpar os dados originais da Equipe 1 e Equipe 2
    'For i = 12 To 112
    '    wsEquipes.Range("A" & i & ":F" & i).ClearContents
    '    wsEquipes.Range("H" & i & ":N" & i).ClearContents
    'Next i

End Sub

