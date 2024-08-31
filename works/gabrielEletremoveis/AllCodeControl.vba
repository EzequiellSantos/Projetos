Dim wsEntradas As Worksheet
Dim wsSaidas As Worksheet
Dim wsBackend As Worksheet
Dim ProdutoEncontrado As Boolean


Dim i As Long
Dim e As Long
Dim LastRow1 As Long
Dim id As Long
Dim Quant As Double
Dim cod As Double
Dim Nome As String
Dim LastRow As Long
Dim h As Long
Dim Valor As Double
'Busca de produtos da tabela de entrada
Sub BuscarProdutoPorNomeEntradas()

    
    ' Limpar a tabela de busca na aba "Entradas"
    ThisWorkbook.Sheets("Entradas").Range("H9:K109").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")

    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 9 ' Linha inicial na tabela "Entradas"
    
    For i = 822 To LastRow ' Começar a busca a partir da célula H9
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Entradas
            ThisWorkbook.Sheets("Entradas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Entradas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Entradas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Entradas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
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

Sub BuscarProdutoPorNomeEntradasTwo()

    ' Limpar a tabela de busca na aba "Entradas"
    ThisWorkbook.Sheets("Entradas").Range("H115:K215").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 115 ' Linha inicial na tabela "Entradas"
    ProdutoEncontrado = False ' Flag para verificar se o produto foi encontrado
    
    For i = 822 To LastRow ' Começar a busca a partir da primeira linha da tabela "Back-end"
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Entradas"
            ThisWorkbook.Sheets("Entradas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Entradas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Entradas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Entradas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
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

Sub BuscarProdutoPorNomeEntradasThre()
    
    ' Limpar a tabela de busca na aba "Entradas"
    ThisWorkbook.Sheets("Entradas").Range("H221:K321").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 221 ' Linha inicial na tabela "Entradas"
    ProdutoEncontrado = False ' Flag para verificar se o produto foi encontrado
    
    For i = 822 To LastRow ' Começar a busca a partir da primeira linha da tabela "Back-end"
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Entradas"
            ThisWorkbook.Sheets("Entradas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Entradas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Entradas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Entradas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
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

Sub BuscarProdutoPorNomeEntradasFour()
    
    ' Limpar a tabela de busca na aba "Entradas"
    ThisWorkbook.Sheets("Entradas").Range("H327:K427").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 327 ' Linha inicial na tabela "Entradas"
    ProdutoEncontrado = False ' Flag para verificar se o produto foi encontrado
    
    For i = 822 To LastRow ' Começar a busca a partir da primeira linha da tabela "Back-end"
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Entradas"
            ThisWorkbook.Sheets("Entradas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Entradas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Entradas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Entradas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
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

Sub BuscarProdutoPorNomeEntradasFive()
    
    ' Limpar a tabela de busca na aba "Entradas"
    ThisWorkbook.Sheets("Entradas").Range("H433:K533").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "#GT$"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Back-end"
    LastRow = 1022
    
    h = 433 ' Linha inicial na tabela "Entradas"
    ProdutoEncontrado = False ' Flag para verificar se o produto foi encontrado
    
    For i = 822 To LastRow ' Começar a busca a partir da primeira linha da tabela "Back-end"
        If InStr(1, ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Entradas"
            ThisWorkbook.Sheets("Entradas").Cells(h, 8).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 28).Value ' Código
            ThisWorkbook.Sheets("Entradas").Cells(h, 9).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 29).Value ' Nome
            ThisWorkbook.Sheets("Entradas").Cells(h, 10).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 31).Value ' fornecedor
            ThisWorkbook.Sheets("Entradas").Cells(h, 11).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value ' quantidade
            
            ProdutoEncontrado = True ' Define a flag como verdadeira
            
            If h < 533 Then
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

'Código de navegação para as SubTabelas de Entradas

Sub NavegarEntradasCompras()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 11
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, coluna).Select

End Sub

Sub NavegarEntradasCaminhaoAzul()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 117
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, coluna).Select

End Sub

Sub NavegarEntradasCaminhaoVerm()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 223
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, coluna).Select

End Sub

Sub NavegarEntradasCatalog1()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 329
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, coluna).Select

End Sub

Sub NavegarEntradasCatalog2()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 435
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Entradas").Activate
    ThisWorkbook.Sheets("Entradas").Cells(ultimaLinha, coluna).Select

End Sub

'Código de navegação para SubTabelas de Saidas

Sub NavegarSaidasCaminhaoAzul()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 11
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, coluna).Select

End Sub

Sub NavegarSaidasCaminhaoVerm()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 117
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, coluna).Select

End Sub

Sub NavegarSaidasCatalogo1()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 223
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, coluna).Select

End Sub

Sub NavegarSaidasCatalogo2()
    Dim coluna As String
    Dim ultimaLinha As Long
    
    ' Defina a coluna para onde deseja ir (por exemplo, "A" para a coluna A)
    coluna = "F"
    
    ' Encontre a última linha na coluna especificada
    ultimaLinha = 329
    
    ' Vá para a célula na última linha da coluna especificada
    ThisWorkbook.Sheets("Saidas").Activate
    ThisWorkbook.Sheets("Saidas").Cells(ultimaLinha, coluna).Select

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
    Sheets("Cadastro").Activate
End Sub

Sub NavegarParaVendas()
    Sheets("Estoque Atual").Activate
End Sub
Sub NavegarParaMovimentos()
    Sheets("Movimentos").Activate
End Sub

Sub FinalizarSemanaEntradas()

    ' Definir a planilha "Entradas"
    Set wsEntradas = ThisWorkbook.Sheets("Entradas")
    Set wsBackend = ThisWorkbook.Sheets("Back-end")

    coletarCompras
    coletarCaminhaoAzul
    coletarCaminhaoVerm
    coletarCatalogoClev
    coletarCatalogoMarc
    
    LimparIntervalos


End Sub

Sub coletarCompras()

    LastRow1 = 204

    ' Transferir os dados para a Equipe 1
    For i = 4 To LastRow1

        For e = 9 To 109

            cod = ThisWorkbook.Sheets("Entradas").Cells(e, 1).Value
            Quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


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
            Quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


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
            Quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


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
            Quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


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
            Quant = ThisWorkbook.Sheets("Entradas").Cells(e, 3).Value


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


Sub FinalizarSemanaSaidas()

    Set wsBackend = ThisWorkbook.Sheets("Back-end")
    ' Definir a planilha "Saidas"
    Set wsSaidas = ThisWorkbook.Sheets("Saidas")

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
            Quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


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
            Quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


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
            Quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


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
            Quant = ThisWorkbook.Sheets("Saidas").Cells(e, 3).Value


            If ThisWorkbook.Sheets("Back-end").Cells(i, 1).Value = cod Then
                
                'coletar os ids digitados na planilha Saidas
                ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value = ThisWorkbook.Sheets("Back-end").Cells(i, 34).Value + Quant ' Adicionar a nova quantidade à quantidade atual

            End If

            

        Next e

            
    Next i

End Sub

Sub finalizarMes()

    atualizarEstoqueMes
    
    LimparIntervaloSBackEnd
    
End Sub

Sub LimparIntervaloSBackEnd()
    Dim rng1 As Range

    ' Define os intervalos especificados na planilha Back-end
    Set rng1 = Sheets("Back-end").Range("B4:B204, F4:F204, V4:V204, Z4:Z204, J4:J204, AD4:AD204, N4:N204, AH4:AH204, R4:R204") ' coluna A

    ' Limpa os intervalos
    rng1.ClearContents

  
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

' enviar dados da quantidade atual do backend para a tabela de estoque
Sub atualizarEstoqueMes()
    Dim wsBackend As Worksheet
    Dim wsEstoque As Worksheet
    Dim i As Long
    Dim linhaEstoque As Long

    ' Definir a planilha "Back-end"
    Set wsBackend = ThisWorkbook.Sheets("Back-end")

    ' Definir a planilha "Estoque"
    Set wsEstoque = ThisWorkbook.Sheets("Cadastro")

    linhaCadastro = 3  ' Inicializar a linhaCadastro fora do loop

    ' Transferir os dados da tabela back-end para Cadastro
    For i = 822 To 1022

        If Not IsEmpty(wsBackend.Cells(i, 34).Value) Then

            wsCadastro.Cells(linhaCadastro, 4).Value = wsBackend.Cells(i, 34).Value ' Quantidade
            linhaCadastro = linhaCadastro + 1

        End If

    Next i
End Sub



