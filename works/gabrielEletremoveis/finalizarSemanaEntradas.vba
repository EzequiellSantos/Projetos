Dim wsEntradas As Worksheet
Dim wsBackEnd As Worksheet
Dim i As Long
Dim e As Long
Dim LastRow1 As Long
Dim id As Long
Dim quant As Double
Dim cod As Double
Dim codigosEntrada() As Variant
Dim quantidadesEntrada() As Variant

' Definir a planilha "Equipes"
Set wsEntradas = ThisWorkbook.Sheets("Entradas")
Set wsBackEnd = ThisWorkbook.Sheets("Back-end")

Sub FinalizarSemanaEntradas()
    coletarDados "coletarCompras", 4, 204, 9, 109, 2
    coletarDados "coletarCaminhaoVerm", 4, 204, 221, 321, 6
    coletarDados "coletarCaminhaoAzul", 4, 204, 115, 215, 10
    coletarDados "coletarCatalogoClev", 4, 204, 327, 427, 14
    coletarDados "coletarCatalogoMarc", 4, 204, 433, 533, 18
End Sub

Sub coletarDados(nomeSub As String, startI As Long, endI As Long, startE As Long, endE As Long, coluna As Long)
    Dim i As Long, e As Long
    Dim cod As Double
    Dim quant As Double
    Dim LastRow1 As Long
    Dim codigosEntrada() As Variant
    Dim quantidadesEntrada() As Variant
    
    LastRow1 = endI

    ' Carregar os códigos e quantidades da planilha "Entradas" em arrays
    With wsEntradas
        codigosEntrada = .Range(.Cells(startE, 1), .Cells(endE, 1)).Value
        quantidadesEntrada = .Range(.Cells(startE, 3), .Cells(endE, 3)).Value
    End With

    For i = startI To LastRow1
        For e = LBound(codigosEntrada, 1) To UBound(codigosEntrada, 1)
            cod = codigosEntrada(e, 1)
            quant = quantidadesEntrada(e, 1)
            
            If wsBackEnd.Cells(i, 1).Value = cod Then
                wsBackEnd.Cells(i, coluna).Value = wsBackEnd.Cells(i, coluna).Value + quant
                wsEntradas.Cells(startE + e - 1, 1).ClearContents
            End If
        Next e
    Next i
End Sub
