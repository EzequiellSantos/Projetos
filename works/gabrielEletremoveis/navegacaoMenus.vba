'Código de navegação para as SubTabelas de Entradas

Sub NavegarEntradasCompras()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 11
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, Coluna).Select

End Sub

Sub NavegarEntradasCaminhaoAzul()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 117
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, Coluna).Select

End Sub

Sub NavegarEntradasCaminhaoVerm()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 223
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, Coluna).Select

End Sub

Sub NavegarEntradasCatalog1()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 329
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, Coluna).Select

End Sub

Sub NavegarEntradasCatalog2()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 435
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, Coluna).Select

End Sub

'Código de navegação para SubTabelas de Saidas

Sub NavegarSaidasCaminhaoAzul()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 11
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, Coluna).Select

End Sub

Sub NavegarSaidasCaminhaoVerm()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 117
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, Coluna).Select

End Sub

Sub NavegarSaidasCatalogo1()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 223
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, Coluna).Select

End Sub

Sub NavegarSaidasCatalogo2()
    Dim Coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    Coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 329
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, Coluna).Select

End Sub


Private Sub Workbook_Open()
    ' Exibir a planilha TelaInicial ao abrir a pasta de trabalho
    Sheets("Inicio").Activate
End Sub

'Navegação entre as planilhas

Sub NavegarParaEntradas()
    Sheets("Entradas").Activate
End Sub

Sub NavegarParaInicio()
    Sheets("Inicio").Activate
End Sub

Sub NavegarParaSaidas()
    Sheets("Saidas").Activate
End Sub

Sub NavegarParaEstoque()
    Sheets("Estoque").Activate
End Sub

Sub NavegarParaMovimentos()
    Sheets("Movimentos").Activate
End Sub

Sub NavegarParaVendas()
    Sheets("Para Vendendores").Activate
End Sub