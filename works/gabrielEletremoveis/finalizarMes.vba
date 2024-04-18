Sub atualizarEstoqueMes()
    Dim wsBackend As Worksheet
    Dim wsEstoque As Worksheet
    Dim i As Long
    Dim linhaEstoque As Long

    ' Definir a planilha "Back-end"
    Set wsBackend = ThisWorkbook.Sheets("Back-end")

    ' Definir a planilha "Estoque"
    Set wsEstoque = ThisWorkbook.Sheets("Estoque")

    linhaEstoque = 3  ' Inicializar a linhaEstoque fora do loop

    ' Transferir os dados da tabela back-end para Estoque
    For i = 822 To 1022

        If Not IsEmpty(wsBackend.Cells(i, 34).Value) Then

            wsEstoque.Cells(linhaEstoque, 4).Value = wsBackend.Cells(i, 34).Value ' Quantidade
            linhaEstoque = linhaEstoque + 1

        End If

    Next i
End Sub
