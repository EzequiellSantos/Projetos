'Busca de Produtos da tabela de Saidas
Sub BuscarProdutoPorNomeSaidas()
    ' Limpar a tabela de busca na aba "Reposicao"
    ThisWorkbook.Sheets("Saidas").Range("H9:K109").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")

    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 9 ' Linha inicial na tabela "Reposicao"
    
    For i = 822 To LastRow ' Começar a busca a partir da célula H9
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Reposicao"
            ThisWorkbook.Sheets("Saidas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Saidas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Saidas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Saidas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
            If h <= 109 Then
                h = h + 1
            Else
                h = 109
            End If
            
        End If


    Next i
    
    
    ' Caso nenhum produto seja encontrado
    If h = 9 Then
        MsgBox "Produto não encontrado!", vbExclamation, "Erro"
    End If
    
    
    
End Sub


Sub BuscarProdutoPorNomeSaidasTwo()
    
    ' Limpar a tabela de busca na aba "Saidas"
    ThisWorkbook.Sheets("Saidas").Range("H115:K215").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 115 ' Linha inicial na tabela "Saidas"
    ProdutoEncontrado = False ' Flag para verificar se o produto foi encontrado
    
    For i = 822 To LastRow ' Começar a busca a partir da primeira linha da tabela "Back-end"
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Saidas"
            ThisWorkbook.Sheets("Saidas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Saidas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Saidas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Saidas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
            ProdutoEncontrado = True ' Define a flag como verdadeira
            
            If h < 215 Then
                h = h + 1
            Else
                Exit For ' Se atingir o limite de linhas, sai do loop
            End If
        End If
    Next i
    
    ' Caso nenhum produto seja encontrado
    If Not ProdutoEncontrado Then
        MsgBox "Produto não encontrado!", vbExclamation, "Erro"
    End If
End Sub

Sub BuscarProdutoPorNomeSaidasThre()
    
    ' Limpar a tabela de busca na aba "Saidas"
    ThisWorkbook.Sheets("Saidas").Range("H221:K321").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 221 ' Linha inicial na tabela "Saidas"
    ProdutoEncontrado = False ' Flag para verificar se o produto foi encontrado
    
    For i = 822 To LastRow ' Começar a busca a partir da primeira linha da tabela "Back-end"
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Saidas"
            ThisWorkbook.Sheets("Saidas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Saidas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Saidas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Saidas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
            ProdutoEncontrado = True ' Define a flag como verdadeira
            
            If h < 321 Then
                h = h + 1
            Else
                Exit For ' Se atingir o limite de linhas, sai do loop
            End If
        End If
    Next i
    
    ' Caso nenhum produto seja encontrado
    If Not ProdutoEncontrado Then
        MsgBox "Produto não encontrado!", vbExclamation, "Erro"
    End If
End Sub

Sub BuscarProdutoPorNomeSaidasFour()
    
    ' Limpar a tabela de busca na aba "Saidas"
    ThisWorkbook.Sheets("Saidas").Range("H327:K427").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 327 ' Linha inicial na tabela "Saidas"
    ProdutoEncontrado = False ' Flag para verificar se o produto foi encontrado
    
    For i = 822 To LastRow ' Começar a busca a partir da primeira linha da tabela "Back-end"
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Saidas"
            ThisWorkbook.Sheets("Saidas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Saidas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Saidas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Saidas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
            ProdutoEncontrado = True ' Define a flag como verdadeira
            
            If h < 427 Then
                h = h + 1
            Else
                Exit For ' Se atingir o limite de linhas, sai do loop
            End If
        End If
    Next i
    
    ' Caso nenhum produto seja encontrado
    If Not ProdutoEncontrado Then
        MsgBox "Produto não encontrado!", vbExclamation, "Erro"
    End If
End Sub