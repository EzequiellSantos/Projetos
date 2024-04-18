Dim wsSaidas As Worksheet
Dim wsBackEnd AS Worksheet

' Definir a planilha "Equipes"
Set wsSaidas = ThisWorkbook.Sheets("Saidas")
Set wsBackEnd = ThisWorkbook.Sheets("Back-end")

Sub FinalizarSemanaSaidas()

    coletarCaminhaoAzul2
    coletarCaminhaoVerm2
    coletarCatalogoClev2
    coletarCatalogoMarc2

    LimparIntervalos2


End Sub

Sub coletarCaminhaoAzul2()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 9 To 109

            cod = ThisWorkbook.Sheets("Saidas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha Saidas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 26).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 26).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub coletarCatalogoClev2()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 221 To 321

            cod = ThisWorkbook.Sheets("Saidas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha Saidas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 30).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 30).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub coletarCaminhaoVerm2()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 115 To 215

            cod = ThisWorkbook.Sheets("Saidas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha Saidas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 22).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 22).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub coletarCatalogoMarc2()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 327 To 427

            cod = ThisWorkbook.Sheets("Saidas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha Saidas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub LimparIntervalos2()
    Dim rng1 As Range, rgn2 As Range
    

    ' Define os intervalos especificados na planilha Saidas
    Set rng1 = Sheets("Saidas").Range("A9:A109,A115:A215,A221:A321,A327:A427") ' coluna A
    Set rng2 = Sheets("Saidas").Range("C9:C109,C115:C215,C221:C321,C327:C427") ' coluna C

    ' Limpa os intervalos
    rng1.ClearContents
    rng2.ClearContents
  
End Sub

Sub LimparIntervaloSBackEnd()
    Dim rng1 As Range

    ' Define os intervalos especificados na planilha Back-end
    Set rng1 = Sheets("Back-end").Range("B4:B204, F4:F204, V4:V204, Z4:Z204, J4:J204, AD4:AD204, N4:N204, AH4:AH204, R4:R204") ' coluna A

    ' Limpa os intervalos
    rng1.ClearContents

  
End Sub

