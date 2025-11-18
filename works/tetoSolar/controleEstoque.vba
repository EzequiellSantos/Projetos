Dim LastRow As Long

Sub VerificarDuplicatas(coluna As String)
    Dim ws As Worksheet
    Dim dict As Object
    Dim ultimaLinha As Long
    Dim i As Long
    Dim valor As String
    Dim duplicatas As Boolean
    Dim duplicatasList As String
    
    ' Definir a planilha ativa
    Set ws = ActiveSheet
    
    ' Criar um dicionário para rastrear valores únicos
    Set dict = CreateObject("Scripting.Dictionary")
    
    ' Encontrar a última linha da coluna especificada
    ultimaLinha = ws.Cells(ws.Rows.Count, coluna).End(xlUp).Row
    
    ' Inicializar variáveis
    duplicatas = False
    duplicatasList = "Valores duplicados encontrados:" & vbCrLf
    
    ' Percorrer todas as células da coluna especificada
    For i = 1 To ultimaLinha
        valor = ws.Cells(i, coluna).Value
        If dict.exists(valor) Then
            ' Se o valor já existir no dicionário, marcar como duplicata
            duplicatas = True
            duplicatasList = duplicatasList & valor & " (Linha " & i & ")" & vbCrLf
        Else
            ' Adicionar o valor ao dicionário
            dict(valor) = True
        End If
    Next i
    
    ' Exibir mensagem de aviso se houver duplicatas
    If duplicatas Then
        MsgBox duplicatasList, vbExclamation
    Else
        MsgBox "Não há valores duplicados na coluna " & coluna & ".", vbInformation
    End If
End Sub


Sub TestarDuplicatas()
    VerificarDuplicatas "A"
End Sub



Sub EnviarCadastro()
    Dim wsCadastro As Worksheet, wsEstoque As Worksheet
    Dim novoID As String
    Dim LastRow As Long
    
    ' Definir as planilhas
    Set wsCadastro = ThisWorkbook.Sheets("Cadastro")
    Set wsEstoque = ThisWorkbook.Sheets("Estoque")
    
    ' Encontrar a última linha na coluna A da planilha "Estoque"
    LastRow = wsEstoque.Cells(wsEstoque.Rows.Count, "A").End(xlUp).Row + 1
    
    ' Definir o tipo do produto (os dois primeiros caracteres do nome)
    Dim tipo As String
    tipo = Left(wsCadastro.Range("B5").Value, 2)
    
    ' Validar se o tipo é IM, UC ou MP
   ' If tipo <> "IM" And tipo <> "UC" And tipo <> "MP" Then
        'MsgBox "Tipo de produto inválido. Deve ser 'IM', 'UC' ou 'MP'.", vbExclamation
        'Exit Sub
    'End If
    
    ' Criar um dicionário para rastrear os IDs existentes
    Dim dict As Object
    Set dict = CreateObject("Scripting.Dictionary")
    
    Dim linha As Long
    Dim currentID As String
    Dim currentNum As Long
    
    ' Procurar todos os IDs do mesmo tipo
    For linha = 1 To wsEstoque.Cells(wsEstoque.Rows.Count, "A").End(xlUp).Row
        currentID = wsEstoque.Cells(linha, 1).Value
        If Left(currentID, 2) = tipo Then
            currentNum = Val(Right(currentID, 4))
            dict(currentNum) = True
        End If
    Next linha
    
    ' Encontrar o menor número disponível na sequência
    Dim i As Long
    For i = 1 To dict.Count + 1
        If Not dict.exists(i) Then
            novoID = tipo & Format(i, "0000")
            Exit For
        End If
    Next i
    
    ' Copiar valores das células de cadastro para a planilha "Estoque"
    wsEstoque.Cells(LastRow, 1).Value = novoID
    wsEstoque.Cells(LastRow, 2).Value = wsCadastro.Range("B1").Value
    wsEstoque.Cells(LastRow, 3).Value = wsCadastro.Range("B2").Value
    wsEstoque.Cells(LastRow, 4).Value = wsCadastro.Range("B3").Value
    wsEstoque.Cells(LastRow, 5).Value = wsCadastro.Range("B4").Value
    wsEstoque.Cells(LastRow, 6).Value = wsCadastro.Range("B6").Value
    wsEstoque.Cells(LastRow, 7).Value = wsCadastro.Range("B7").Value
    
    ' Limpar células de cadastro
    wsCadastro.Range("B1:B7").ClearContents
    
    ' MsgBox "Cadastro enviado com sucesso!", vbInformation
End Sub
    
Sub BuscarProdutoPorNome()
    Dim Nome As String
    Dim LastRow As Long
    Dim i As Long
    Dim j As Long
    Dim Quant As Double
    Dim valor As Double
    
    ' Limpar a tabela de busca na aba "Reposicao"
    ThisWorkbook.Sheets("Reposicao").Range("J4:M100").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "$f$g0"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Estoque"
    LastRow = ThisWorkbook.Sheets("Estoque").Cells(ThisWorkbook.Sheets("Estoque").Rows.Count, "B").End(xlUp).Row
    
    j = 4 ' Linha inicial na tabela "Reposicao"
    
    For i = 4 To LastRow ' Começar a busca a partir da célula B4
        If InStr(1, ThisWorkbook.Sheets("Estoque").Cells(i, 2).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Reposicao"
            ThisWorkbook.Sheets("Reposicao").Cells(j, 10).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 1).Value ' Código
            ThisWorkbook.Sheets("Reposicao").Cells(j, 11).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 2).Value ' Nome
            ThisWorkbook.Sheets("Reposicao").Cells(j, 12).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 3).Value ' Quantidade
            ThisWorkbook.Sheets("Reposicao").Cells(j, 13).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 4).Value ' Valor
            
            If j <= 19 Then
                j = j + 1
            Else
                j = 20
            End If
        End If
    Next i
    
    ' Inserir data atual na tabela "Reposicao"
    ThisWorkbook.Sheets("Reposicao").Range("A5").Value = "Data"
    
    ' Caso nenhum produto seja encontrado
    If j = 4 Then
        MsgBox "Produto não encontrado!", vbExclamation, "Erro"
    End If
    
    CriarDropdownOne
    
    
End Sub

Sub BuscarProdutoPorNometTwo()
    Dim Nome As String
    Dim LastRow As Long
    Dim i As Long
    Dim j As Long
    Dim Quant As Double
    Dim valor As Double
    
    ' Limpar a tabela de busca na aba "Reposicao"
    ThisWorkbook.Sheets("Saidas").Range("J4:M100").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "$f$g0"
    End If
    
    
    ' Buscar os produtos com o mesmo nome na tabela "Estoque"
    LastRow = ThisWorkbook.Sheets("Estoque").Cells(ThisWorkbook.Sheets("Estoque").Rows.Count, "B").End(xlUp).Row
    
    j = 4 ' Linha inicial na tabela "Reposicao"
    
    For i = 4 To LastRow ' Começar a busca a partir da célula B4
        If InStr(1, ThisWorkbook.Sheets("Estoque").Cells(i, 2).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Reposicao"
            ThisWorkbook.Sheets("Saidas").Cells(j, 10).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 1).Value ' Código
            ThisWorkbook.Sheets("Saidas").Cells(j, 11).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 2).Value ' Nome
            ThisWorkbook.Sheets("Saidas").Cells(j, 12).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 3).Value ' Quantidade
            ThisWorkbook.Sheets("Saidas").Cells(j, 13).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 4).Value ' Valor
            
            If j <= 19 Then
                j = j + 1
            Else
                j = 20
            End If
            
        End If
    Next i
    
    ' Inserir data atual na tabela "Reposicao"
    ThisWorkbook.Sheets("Saidas").Range("A5").Value = "Data"
    
    ' Caso nenhum produto seja encontrado
    If j = 4 Then
        MsgBox "Produto não encontrado!", vbExclamation, "Erro"
    End If
    
    CriarDropdownTwo
    
    
End Sub

Sub AtualizarEstoque()
    Dim Cod As String
    Dim Nome As String
    Dim Quant As Double
    Dim TipoMov As String
    Dim LastRow As Long
    Dim i As Long
    Dim ProdutoEncontrado As Boolean
    
    Cod = ThisWorkbook.Sheets("Reposicao").Range("B1").Value
    Nome = ThisWorkbook.Sheets("Reposicao").Range("B2").Value
    Quant = ThisWorkbook.Sheets("Reposicao").Range("B3").Value
    TipoMov = ThisWorkbook.Sheets("Reposicao").Range("B4").Value

    
    ' Atualizar a quantidade do produto na tabela "Estoque"
    LastRow = ThisWorkbook.Sheets("Estoque").Cells(ThisWorkbook.Sheets("Estoque").Rows.Count, "A").End(xlUp).Row
    
    ProdutoEncontrado = False
    
    For i = 1 To LastRow
        If ThisWorkbook.Sheets("Estoque").Cells(i, 1).Value = Cod And ThisWorkbook.Sheets("Estoque").Cells(i, 2).Value = Nome Then
            ThisWorkbook.Sheets("Estoque").Cells(i, 4).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 4).Value + Quant ' Adicionar a nova quantidade à quantidade atual
            ProdutoEncontrado = True
            Exit For
        End If
    Next i
    
    ' Se o produto não foi encontrado, adicionar um novo registro
    If Not ProdutoEncontrado Then
        ThisWorkbook.Sheets("Estoque").Cells(LastRow + 1, 2).Value = Nome
        ThisWorkbook.Sheets("Estoque").Cells(LastRow + 1, 3).Value = Quant
    End If
    
    ' Adicionar o registro na tabela "Registros"
    LastRow = ThisWorkbook.Sheets("Registros").Cells(ThisWorkbook.Sheets("Registros").Rows.Count, "A").End(xlUp).Row + 1
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 1).Value = Cod
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 2).Value = Nome
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 3).Value = Quant
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 4).Value = TipoMov
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 5).Value = Date
    
    ' Limpar os campos na tabela "Reposicao"
    ThisWorkbook.Sheets("Reposicao").Range("B1,B3").ClearContents
    ThisWorkbook.Sheets("Reposicao").Range("J4:M100").ClearContents
    ThisWorkbook.Sheets("Reposicao").Range("B5").Formula = "=TODAY()"
End Sub
Sub AtualizarEstoqueTwo()
    Dim Cod As String
    Dim Nome As String
    Dim Setor As String
    Dim Quant As Double
    Dim LastRow As Long
    Dim i As Long
    Dim ProdutoEncontrado As Boolean
    
    Cod = ThisWorkbook.Sheets("Saidas").Range("B1").Value
    Nome = ThisWorkbook.Sheets("Saidas").Range("B2").Value
    Quant = ThisWorkbook.Sheets("Saidas").Range("B3").Value
    Setor = ThisWorkbook.Sheets("Saidas").Range("B4").Value
    
    ' Atualizar a quantidade do produto na tabela "Estoque"
    LastRow = ThisWorkbook.Sheets("Estoque").Cells(ThisWorkbook.Sheets("Estoque").Rows.Count, "A").End(xlUp).Row
    
    ProdutoEncontrado = False
    
    For i = 1 To LastRow
        If ThisWorkbook.Sheets("Estoque").Cells(i, 1).Value = Cod And ThisWorkbook.Sheets("Estoque").Cells(i, 2).Value = Nome Then
            ThisWorkbook.Sheets("Estoque").Cells(i, 4).Value = ThisWorkbook.Sheets("Estoque").Cells(i, 4).Value - Quant ' remover a nova quantidade à quantidade atual
            ProdutoEncontrado = True
            Exit For
        End If
    Next i
    
    ' Adicionar o registro na tabela "Registros"
    LastRow = ThisWorkbook.Sheets("Registros").Cells(ThisWorkbook.Sheets("Registros").Rows.Count, "G").End(xlUp).Row + 1
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 7).Value = Cod
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 8).Value = Nome
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 9).Value = -Quant
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 10).Value = Setor
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 11).Value = Date

    
    ' Registrando os dados à equipe
    Dim EquipeRow As Long
    Dim ColOffset As Integer
    Dim LastEquipeRow As Long
    
    Select Case Setor
        Case "EQUIPE 1"
            EquipeRow = 12
            ColOffset = 1
        Case "EQUIPE 2"
            EquipeRow = 12
            ColOffset = 9
        Case "EQUIPE 3"
            EquipeRow = 12
            ColOffset = 17
        Case "EQUIPE 4"
            EquipeRow = 12
            ColOffset = 25
        Case "EQUIPE 5"
            EquipeRow = 12
            ColOffset = 33
        Case "MANUTENÇÃO"
            EquipeRow = 12
            ColOffset = 41
            
        Case "ELETRECISTAS"
            EquipeRow = 12
            ColOffset = 49
            
        Case "EQUIPE 6"
            EquipeRow = 12
            ColOffset = 57
            
        Case "ALMOXARIFADO"
            EquipeRow = 12
            ColOffset = 65
        
        Case "LOJA"
            EquipeRow = 12
            ColOffset = 73
            
    End Select
    
    ' Encontrar a última linha dentro do intervalo especificado
    LastEquipeRow = ThisWorkbook.Sheets("Equipes").Cells(ThisWorkbook.Sheets("Equipes").Rows.Count, ColOffset).End(xlUp).Row
    
    If LastEquipeRow < EquipeRow Then
        LastEquipeRow = EquipeRow
    End If
    
    ThisWorkbook.Sheets("Equipes").Cells(LastEquipeRow + 1, ColOffset).Value = Cod
    ThisWorkbook.Sheets("Equipes").Cells(LastEquipeRow + 1, ColOffset + 1).Value = Nome
    ThisWorkbook.Sheets("Equipes").Cells(LastEquipeRow + 1, ColOffset + 2).Value = Quant
    ThisWorkbook.Sheets("Equipes").Cells(LastEquipeRow + 1, ColOffset + 3).Value = Date
    
    ' Limpar os campos na tabela "Saidas"
    ThisWorkbook.Sheets("Saidas").Range("B1,B3").ClearContents
    ThisWorkbook.Sheets("Saidas").Range("J4:M100").ClearContents
    ThisWorkbook.Sheets("Saidas").Range("B5").Formula = "=TODAY()"
End Sub


Sub AplicarFormatacaoCondicional()

    Dim ws As Worksheet
    Dim rngD As Range, rngE As Range
    Dim cell As Range
    Dim cond1 As FormatCondition
    Dim valorD As Double, valorE As Double
    Dim diferenca As Double
    Dim porcentagem As Double
    
    ' Definindo a planilha
    Set ws = ThisWorkbook.Sheets("Estoque")
    
    ' Definindo os intervalos das colunas D e E
    Set rngD = ws.Range("D4:D500")
    Set rngE = ws.Range("E4:E500")
    
    ' Limpar formatação condicional anterior
    rngD.FormatConditions.Delete
    
    ' Aplicar formatação condicional
    For Each cell In rngD
    
        ' Verifica se o valor da célula é numérico
        If IsNumeric(cell.Value) Then
            valorD = cell.Value
        Else
            valorD = 0
        End If
    
        ' Verifica se o valor da célula à direita é numérico
        If IsNumeric(cell.Offset(0, 1).Value) Then
            valorE = cell.Offset(0, 1).Value
        Else
            valorE = 0
        End If
        
        ' Verificar se os valores de D e E são iguais
        If valorD = valorE And valorE <> 0 Then
            cell.Interior.Color = RGB(255, 255, 0) ' Cor amarela
            GoTo Proximo
        Else
            cell.Interior.Color = RGB(255, 255, 255) ' Cor branca
        End If
        
        ' Verificar se D é maior que E e calcular a porcentagem da diferença
        If valorD > valorE Then
            diferenca = valorD - valorE
            
            ' Verificar se o denominador é zero
            If valorE <> 0 Then
                porcentagem = (diferenca / valorE) * 100
            Else
                porcentagem = 0
            End If
            
            ' Criar a condição
            Set cond1 = cell.FormatConditions.Add(Type:=xlCellValue, Operator:=xlGreater, Formula1:="=" & cell.Offset(0, 1).Address)
            
            ' Definir a cor com base na porcentagem
            With cell.FormatConditions.Item(1)
                .SetFirstPriority ' Garante que esta é a primeira regra a ser verificada
                .StopIfTrue = False
                
                If porcentagem = 0 Then
                
                    .Interior.Color = RGB(0, 255, 0) ' Cor verde
                
                ElseIf porcentagem >= 50 Then
                    .Interior.Color = RGB(0, 255, 0) ' Cor verde
                    
                ElseIf porcentagem < 50 Then
                    .Interior.Color = RGB(255, 240, 33) ' Cor amarela
                
                ElseIf porcentagem = 100 Then
                
                    .Interior.Color = RGB(0, 255, 0) ' preto
                
                Else
                    .Interior.Color = RGB(0, 0, 0) ' Cor branca
                End If
            End With
        Else
            ' Criar a condição para o caso de D ser menor que E
            Set cond1 = cell.FormatConditions.Add(Type:=xlCellValue, Operator:=xlLess, Formula1:="=" & cell.Offset(0, 1).Address)
            
            ' Definir a cor vermelha
            With cell.FormatConditions.Item(1)
                .SetFirstPriority ' Garante que esta é a primeira regra a ser verificada
                .StopIfTrue = False
                .Interior.Color = RGB(255, 0, 0) ' Cor vermelha
            End With
        End If
        
Proximo:
    Next cell

End Sub

Sub CriarTelaInicial()

    Dim ws As Worksheet
    Dim btn As Object
    Dim i As Integer
    Dim nomes As Variant
    Dim links As Variant
    Dim leftPos As Integer
    Dim topPos As Integer
    
    ' Nomes das planilhas
    nomes = Array("Cadastro", "Estoque", "Reposicao", "Saidas", "Registros", "Equipes")
    
    ' Links das planilhas
    links = Array("Cadastro", "Estoque", "Reposicao", "Saidas", "Registros", "Equipes")
    
    ' Criar a planilha "TelaInicial" se não existir
    On Error Resume Next
    Application.DisplayAlerts = False
    Sheets("Inicio").Delete
    On Error GoTo 0
    Application.DisplayAlerts = True
    
    Set ws = ThisWorkbook.Worksheets.Add
    ws.Name = "Inicio"
    
    ' Criar botões de navegação
    leftPos = 50
    topPos = 50
    For i = LBound(nomes) To UBound(nomes)
        Set btn = ws.Buttons.Add(leftPos, topPos + (i * 30), 100, 20)
        btn.OnAction = "NavegarPara" & links(i)
        btn.Caption = nomes(i)
    Next i

End Sub

Sub NavegarParaSheet1()
    Sheets("Cadastro").Activate
End Sub

Sub NavegarParaSheet2()
    Sheets("Estoque").Activate
End Sub

Sub NavegarParaSheet3()
    Sheets("Reposicao").Activate
End Sub

Sub NavegarParaSheet4()
    Sheets("Saidas").Activate
End Sub

Sub NavegarParaSheet5()
    Sheets("Registros").Activate
End Sub

Sub NavegarParaSheet6()
    Sheets("Equipes").Activate
End Sub

Sub NavegarParaOInicio()
    Sheets("Inicio").Activate
End Sub
Sub CriarDropdownSetores()
    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    Dim UltimoSetor As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Saidas") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B4") ' Célula onde o dropdown será criado
    Set rngValor = ws.Range("B4") ' Célula que será preenchida com o valor selecionado
    
    ' Defina os valores da lista suspensa
    Lista = "EQUIPE 1,EQUIPE 2,EQUIPE 3,EQUIPE 4,EQUIPE 5, EQUIPE 6, MANUTENÇÃO, ELETRECISTAS, ALMOXARIFADO, LOJA"
    
    ' Verifique se a célula tem um valor anteriormente selecionado
    If Not IsEmpty(rngValor.Value) Then
        UltimoSetor = rngValor.Value
    End If
    
    ' Crie a lista suspensa na célula
    With rngDropdown.Validation
        .Delete ' Certifique-se de limpar qualquer validação existente
        .Add Type:=xlValidateList, AlertStyle:=xlValidAlertStop, Formula1:=Lista
        .IgnoreBlank = True
        .InCellDropdown = True
        .ShowInput = True
        .ShowError = True
    End With
    
    ' Defina o valor inicial do dropdown como o último setor selecionado
    If UltimoSetor <> "" Then
        rngDropdown.Value = UltimoSetor
    End If
End Sub


Sub CriarDropdowntTipos()

    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Cadastro") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B5") ' Célula onde o dropdown será criado
    Set rngValor = ws.Range("B5") ' Célula que será preenchida com o valor selecionado

    ' Defina os valores da lista suspensa
    Lista = "MP, IM, UC"
    
    ' Crie a lista suspensa na célula
    With rngDropdown.Validation
        .Delete
        .Add Type:=xlValidateList, AlertStyle:=xlValidAlertStop, Operator:= _
        xlBetween, Formula1:=Lista
        .IgnoreBlank = True
        .InCellDropdown = True
        .ShowInput = True
        .ShowError = True
    End With

End Sub

Sub CriarDropdowntTiposMedida()

    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Cadastro") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B6") ' Célula onde o dropdown será criado
    Set rngValor = ws.Range("B6") ' Célula que será preenchida com o valor selecionado

    ' Defina os valores da lista suspensa
    Lista = "UN, M, PC, PAR"
    
    ' Crie a lista suspensa na célula
    With rngDropdown.Validation
        .Delete
        .Add Type:=xlValidateList, AlertStyle:=xlValidAlertStop, Operator:= _
        xlBetween, Formula1:=Lista
        .IgnoreBlank = True
        .InCellDropdown = True
        .ShowInput = True
        .ShowError = True
    End With

End Sub
Sub CriarDropdownTiposMov()

    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Reposicao") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B4") ' Célula onde o dropdown será criado
    Set rngValor = ws.Range("B4") ' Célula que será preenchida com o valor selecionado
    
    ' Defina os valores da lista suspensa
    Lista = "COMPRA,DEVOLUCAO,CONTAGEM"
    
    ' Crie a lista suspensa na célula
    With rngDropdown.Validation
        .Delete
        .Add Type:=xlValidateList, AlertStyle:=xlValidAlertStop, Operator:= _
        xlBetween, Formula1:=Lista
        .IgnoreBlank = True
        .InCellDropdown = True
        .ShowInput = False
        .ShowError = False
    End With

End Sub

Private Sub Worksheet_Change(ByVal Target As Range)
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim ws As Worksheet
    
    Set ws = ThisWorkbook.Sheets("Reposicao")
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B2") ' Célula onde o dropdown está
    
    ' Verifique se a célula alterada é a célula com o dropdown
    If Not Intersect(Target, rngDropdown) Is Nothing Then
        Application.EnableEvents = False
        rngValor.Value = rngDropdown.Value
        Application.EnableEvents = True
    End If
    
    If Not Intersect(Target, Me.Range("D4:D100")) Is Nothing Then
        AplicarFormatacaoCondicional
    End If
    
    AplicarFormatacaoCondicional
    
    End If
    
End Sub

Private Sub Workbook_Open()
    ' Exibir a planilha TelaInicial ao abrir a pasta de trabalho
    Sheets("Inicio").Activate
    AtivarMacro
End Sub

'fazendo um select para os codigos dos produtos selecionadosb

Sub CriarDropdownOne()

    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Reposicao") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B1") ' Célula onde o dropdown será criado
    
    ' Defina os valores da lista suspensa com base na coluna J4:J10
    Lista = Join(Application.Transpose(ws.Range("J4:J10").Value), ",")
    
    ' Crie a lista suspensa na célula
    With rngDropdown.Validation
        .Delete
        .Add Type:=xlValidateList, Operator:= _
        xlBetween, Formula1:=Lista
        .IgnoreBlank = True
        .InCellDropdown = True
        .ShowInput = False
        .ShowError = False
    End With

End Sub

'Private Sub Worksheet_ChangeOne(ByVal Target As Range)
   ' Dim rngDropdown As Range
    'Dim rngValor As Range
    'Dim ws As Worksheet
    
    'Set ws = ThisWorkbook.Sheets("Reposicao")
    
    ' Defina o intervalo para o dropdown e o valor
    'Set rngDropdown = ws.Range("A2") ' Célula onde o dropdown está
    
    ' Verifique se a célula alterada é a célula com o dropdown
    'If Not Intersect(Target, rngDropdown) Is Nothing Then
      '  Application.EnableEvents = False
    '    rngValor.Value = rngDropdown.Value
     '   Application.EnableEvents = True
    'End If
'End Sub

Sub CriarDropdownTwo()

    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Saidas") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B1") ' Célula onde o dropdown será criado
    
    ' Defina os valores da lista suspensa com base na coluna J4:J10
    Lista = Join(Application.Transpose(ws.Range("J4:J10").Value), ",")
    
    ' Crie a lista suspensa na célula
    With rngDropdown.Validation
        .Delete
        .Add Type:=xlValidateList, Operator:= _
        xlBetween, Formula1:=Lista
        .IgnoreBlank = True
        .InCellDropdown = True
        .ShowInput = False
        .ShowError = False
    End With

End Sub

'Private Sub Worksheet_ChangeTwo(ByVal Target As Range)
    'Dim rngDropdown As Range
    'Dim rngValor As Range
    'Dim ws As Worksheet
    
    'Set ws = ThisWorkbook.Sheets("Saidas")
    
    ' Defina o intervalo para o dropdown e o valor
    'Set rngDropdown = ws.Range("A2") ' Célula onde o dropdown está
    
    ' Verifique se a célula alterada é a célula com o dropdown
    'If Not Intersect(Target, rngDropdown) Is Nothing Then
      '  Application.EnableEvents = False
      '  rngValor.Value = rngDropdown.Value
      '  Application.EnableEvents = True
   ' End If
'End Sub


Sub ChamarFuncao()
    ' Coloque o código da sua função aqui
    AtualizarEstoqueTwo
    
    MsgBox "A função foi chamada!"
End Sub

Sub CapturarTeclas()
    Dim Tecla As String
    Dim Finalizado As Boolean
    
    Finalizado = False
    
    Do While Not Finalizado
        Tecla = ""
        DoEvents
        Tecla = GetKeyPress
        If Tecla <> "" Then
            ' Verifique se a tecla pressionada é a que você deseja
            If Tecla = "f" Then ' Por exemplo, "f" para chamar a função
                ' Chame sua função aqui
                AtualizarEstoqueTwo
                
            End If
        End If
    Loop
End Sub

Function GetKeyPress() As String
    Dim WshShell As Object
    Set WshShell = CreateObject("WScript.Shell")
    GetKeyPress = WshShell.Popup("", 0, "", 0)
End Function














































