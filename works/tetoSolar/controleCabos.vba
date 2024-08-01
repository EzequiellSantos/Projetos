Sub EnviarDados()
    Dim Cod As String
    Dim Nome As String
    Dim Setor As String
    Dim Quant As Double
    Dim Destin As String
    Dim Desc As String
    Dim Data As String
    Dim LastRow As Long
    Dim i As Long
    Dim ProdutoEncontrado As Boolean
    
    Cod = ThisWorkbook.Sheets("Movimentos").Range("B3").Value
    Nome = ThisWorkbook.Sheets("Movimentos").Range("B8").Value
    Quant = ThisWorkbook.Sheets("Movimentos").Range("B4").Value
    Setor = ThisWorkbook.Sheets("Movimentos").Range("B2").Value
    Destin = ThisWorkbook.Sheets("Movimentos").Range("B5").Value
    Desc = ThisWorkbook.Sheets("Movimentos").Range("B6").Value
    Data = ThisWorkbook.Sheets("Movimentos").Range("B7").Value

    
    ' Atualizar a quantidade do produto na tabela "Cabos"
    LastRow = ThisWorkbook.Sheets("Cabos").Cells(ThisWorkbook.Sheets("Cabos").Rows.Count, "A").End(xlUp).Row
    
    ProdutoEncontrado = False

    ' SETTINGS FOR CALC
    
    'For i = 1 To LastRow
    '    If ThisWorkbook.Sheets("Cabos").Cells(i, 1).Value = Cod And ThisWorkbook.Sheets("Cabos").Cells(i, 2).Value = Nome 'Then
    '        ThisWorkbook.Sheets("Cabos").Cells(i, 3).Value = ThisWorkbook.Sheets("Cabos").Cells(i, 3).Value - Quant ' remover a nova quantidade à quantidade atual
    '        ProdutoEncontrado = True
    '        Exit For
    '    End If
    'Next i

    ' SETTINGS FOR REGISTER
    
    '      Adicionar o registro na tabela "Registros"
    'LastRow = ThisWorkbook.Sheets("Registros").Cells(ThisWorkbook.Sheets("Registros").Rows.Count, "G").End(xlUp).Row + 1
    'ThisWorkbook.Sheets("Registros").Cells(LastRow, 7).Value = Cod
    'ThisWorkbook.Sheets("Registros").Cells(LastRow, 8).Value = Nome
    'ThisWorkbook.Sheets("Registros").Cells(LastRow, 9).Value = -Quant
    'ThisWorkbook.Sheets("Registros").Cells(LastRow, 10).Value = Setor
    'ThisWorkbook.Sheets("Registros").Cells(LastRow, 11).Value = Date

    
    ' Registrando os dados à equipe
    Dim EquipeRow As Long
    Dim ColOffset As Integer
    Dim LastEquipeRow As Long
    
    Select Case Setor
        Case "EQUIPE 1"
            EquipeRow = 6
            ColOffset = 1
        Case "EQUIPE 2"
            EquipeRow = 6
            ColOffset = 8
        Case "EQUIPE 3"
            EquipeRow = 6
            ColOffset = 15
        Case "EQUIPE 4"
            EquipeRow = 6
            ColOffset = 22
        Case "EQUIPE 5"
            EquipeRow = 6
            ColOffset = 29
            
        Case "EQUIPE 6"
            EquipeRow = 6
            ColOffset = 36
            
    End Select
    
    'Encontrar a última linha dentro do intervalo especificado
    LastEquipeRow = ThisWorkbook.Sheets("Registros").Cells(ThisWorkbook.Sheets("Registros").Rows.Count, ColOffset).End(xlUp).Row
    If LastEquipeRow < EquipeRow Then
        LastEquipeRow = EquipeRow
    End If
    ThisWorkbook.Sheets("Registros").Cells(LastEquipeRow + 1, ColOffset).Value = Cod
    ThisWorkbook.Sheets("Registros").Cells(LastEquipeRow + 1, ColOffset + 1).Value = Nome
    ThisWorkbook.Sheets("Registros").Cells(LastEquipeRow + 1, ColOffset + 2).Value = Quant
    ThisWorkbook.Sheets("Registros").Cells(LastEquipeRow + 1, ColOffset + 3).Value = Destin
    ThisWorkbook.Sheets("Registros").Cells(LastEquipeRow + 1, ColOffset + 4).Value = Desc
    ThisWorkbook.Sheets("Registros").Cells(LastEquipeRow + 1, ColOffset + 5).Value = Data
    
    ' Limpar os campos na tabela "Movimentos"
    ThisWorkbook.Sheets("Movimentos").Range("B3,B4, B5, B6").ClearContents
    ThisWorkbook.Sheets("Movimentos").Range("A14:B21").ClearContents
    ThisWorkbook.Sheets("Movimentos").Range("B7").Formula = "=TODAY()"
End Sub


Sub CriarDropdownSetores()
    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    Dim UltimoSetor As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Movimentos") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B2") ' Célula onde o dropdown será criado
    Set rngValor = ws.Range("B2") ' Célula que será preenchida com o valor selecionado
    
    ' Defina os valores da lista suspensa
    Lista = "EQUIPE 1,EQUIPE 2,EQUIPE 3,EQUIPE 4,EQUIPE 5, EQUIPE 6"
    
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

Sub BuscarProdutoPorNome()
    Dim Nome As String
    Dim LastRow As Long
    Dim i As Long
    Dim a As Long
    Dim Quant As Double
    Dim valor As Double
    
    ' Limpar a tabela de busca na aba "Movimentos"
    ThisWorkbook.Sheets("Movimentos").Range("A14:B21").ClearContents
    
    ' Caixa de diálogo para digitar o nome do produto
    Nome = InputBox("Digite o Nome do Produto:")
    
    If Nome = "" Then
        Nome = "$f$g0"
    End If
    
    ' Buscar os produtos com o mesmo nome na tabela "Cabos"
    LastRow = ThisWorkbook.Sheets("Cabos").Cells(ThisWorkbook.Sheets("Cabos").Rows.Count, "B").End(xlUp).Row
    
    a = 14 ' Linha inicial na tabela "Movimentos"
    
    For i = 2 To LastRow ' Começar a busca a partir da célula B4
        If InStr(1, ThisWorkbook.Sheets("Cabos").Cells(i, 2).Value, Nome, vbTextCompare) > 0 Then
            ' Preencher os dados na tabela "Movimentos"
            ThisWorkbook.Sheets("Movimentos").Cells(a, 1).Value = ThisWorkbook.Sheets("Cabos").Cells(i, 1).Value ' Código
            ThisWorkbook.Sheets("Movimentos").Cells(a, 2).Value = ThisWorkbook.Sheets("Cabos").Cells(i, 2).Value ' Nome
            
            If a <= 20 Then
                a = a + 1
            Else
                a = 21
            End If
        End If
    Next i
    
    ' Inserir data atual na tabela "Movimentos"
    ThisWorkbook.Sheets("Movimentos").Range("A7").Value = "Data"
    
    ' Caso nenhum produto seja encontrado
    If j = 4 Then
        MsgBox "Produto não encontrado!", vbExclamation, "Erro"
    End If
    
    CriarDropdownOne
    
    
End Sub

Sub CriarDropdownOne()

    Dim ws As Worksheet
    Dim rngDropdown As Range
    Dim rngValor As Range
    Dim Lista As String
    
    ' Defina a planilha
    Set ws = ThisWorkbook.Sheets("Movimentos") ' Defina o nome da sua planilha
    
    ' Defina o intervalo para o dropdown e o valor
    Set rngDropdown = ws.Range("B3") ' Célula onde o dropdown será criado
    
    ' Defina os valores da lista suspensa com base na coluna J4:J10
    Lista = Join(Application.Transpose(ws.Range("A14:A18").Value), ",")
    
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

