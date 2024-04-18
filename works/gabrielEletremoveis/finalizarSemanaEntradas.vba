Dim wsEntradas As Worksheet
Dim wsBackEnd AS Worksheet
Dim i As Long
dim e As long
Dim LastRow1 As Long
Dim id As Long
Dim quant As Double
Dim cod As Double

' Definir a planilha "Equipes"
Set wsEntradas = ThisWorkbook.Sheets("Entradas")
Set wsBackEnd = ThisWorkbook.Sheets("Back-end")

Sub FinalizarSemanaEntradas()

    coletarCompras
    LimparIntervalos


End Sub

Sub coletarCompras()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 9 To 109

            cod = ThisWorkbook.Sheets("Entradas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha entradas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 2).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 2).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub coletarCaminhaoVerm()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 221 To 321

            cod = ThisWorkbook.Sheets("Entradas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha entradas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 6).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 6).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub coletarCaminhaoAzul()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 115 To 215

            cod = ThisWorkbook.Sheets("Entradas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha entradas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 10).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub coletarCatalogoClev()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 327 To 427

            cod = ThisWorkbook.Sheets("Entradas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha entradas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 14).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 14).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub coletarCatalogoMarc()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 433 To 533

            cod = ThisWorkbook.Sheets("Entradas").Cells(e, 1).Value
            quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha entradas  
                ThisWorkbook.Sheets("Back-end").Cells(i, 18).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 18).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub LimparIntervalos()
    Dim rng1 As Range, rgn2 As Range
    

    ' Define os intervalos especificados na planilha Saidas
    Set rng1 = Sheets("Entradas").Range("A9:A109,A115:A215,A221:A321,A327:A427,A433:A533") ' coluna A
    Set rng2 = Sheets("Entradas").Range("C9:C109,C115:C215,C221:C321,C327:C427,C433:C533") ' coluna C

    ' Limpa os intervalos
    rng1.ClearContents
    rng2.ClearContents
  
End Sub
