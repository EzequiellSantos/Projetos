Sub Registrar()
    Dim Plac As String
    Dim Nome As String
    Dim Motorista As String
    Dim Data As Double
    Dim HoraInit As Date
    Dim HoraFini As Date
    Dim KmInit As Double
    Dim KmFini As Double
    Dim KmResult As Double
    Dim LastRow As Long
    Dim i As Long
    Dim ProdutoEncontrado As Boolean
    
    Plac = ThisWorkbook.Sheets("Registrar").Range("B4").Value
    Nome = ThisWorkbook.Sheets("Registrar").Range("C4").Value
    Motorista = ThisWorkbook.Sheets("Registrar").Range("D4").Value
    HoraInit = ThisWorkbook.Sheets("Registrar").Range("E4").Value
    HoraFini = ThisWorkbook.Sheets("Registrar").Range("F4").Value
    KmInit = ThisWorkbook.Sheets("Registrar").Range("G4").Value
    KmFini = ThisWorkbook.Sheets("Registrar").Range("H4").Value
    Data = ThisWorkbook.Sheets("Registrar").Range("I4").Value
    DataFin = ThisWorkbook.Sheets("Registrar").Range("J4").Value
    

    KmResult = KmFini - KmInit
    
    ' Adicionar o registro na tabela "Registros"
    LastRow = ThisWorkbook.Sheets("Registros").Cells(ThisWorkbook.Sheets("Registros").Rows.Count, "A").End(xlUp).Row + 1
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 1).Value = Plac
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 2).Value = Nome
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 3).Value = Motorista
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 7).Value = Data
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 4).Value = HoraInit
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 6).Value = KmResult
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 8).Value = DataFin
    ThisWorkbook.Sheets("Registros").Cells(LastRow, 5).Value = HoraFini

    
    'ThisWorkbook.Sheets("Saidas").Range("E2").Formula = "=TODAY()"
    
    ' Registrando os dados à equipe
    Dim VeiculoRow As Long
    Dim ColOffset As Integer
    Dim LastVeiculoRow As Long
    
    Select Case Plac
        Case "PNH7F67"
            VeiculoRow = 6
            ColOffset = 2
        Case "FXK4G20"
            VeiculoRow = 6
            ColOffset = 9
        Case "NQM1072"
            VeiculoRow = 6
            ColOffset = 16
        Case "POY0184"
            VeiculoRow = 6
            ColOffset = 23
        Case "SBS0C68"
            VeiculoRow = 6
            ColOffset = 30
        Case "SBC0B98"
            VeiculoRow = 6
            ColOffset = 37
        Case "PNQ2E63"
            VeiculoRow = 6
            ColOffset = 44
        Case "RMQ8G76"
            VeiculoRow = 6
            ColOffset = 51
        Case "PNI1B32"
            VeiculoRow = 6
            ColOffset = 58
            
            
    End Select
    
    If Plac = "" Then
        
        MsgBox "Precisa Inserir a Placa do veiculo", vbExclamation, "Erro"
    
        
    Else
            ' Encontrar a última linha dentro do intervalo especificado
            LastVeiculoRow = ThisWorkbook.Sheets("Veiculos").Cells(ThisWorkbook.Sheets("Veiculos").Rows.Count, ColOffset).End(xlUp).Row
            
                If LastVeiculoRow < VeiculoRow Then
                     LastVeiculoRow = VeiculoRow
                End If
    
            ThisWorkbook.Sheets("Veiculos").Cells(LastVeiculoRow + 1, ColOffset).Value = Motorista
            ThisWorkbook.Sheets("Veiculos").Cells(LastVeiculoRow + 1, ColOffset + 1).Value = Data
            ThisWorkbook.Sheets("Veiculos").Cells(LastVeiculoRow + 1, ColOffset + 2).Value = HoraInit
            ThisWorkbook.Sheets("Veiculos").Cells(LastVeiculoRow + 1, ColOffset + 3).Value = KmResult
            ThisWorkbook.Sheets("Veiculos").Cells(LastVeiculoRow + 1, ColOffset + 4).Value = DataFin
            ThisWorkbook.Sheets("Veiculos").Cells(LastVeiculoRow + 1, ColOffset + 4).Value = HoraFini
            
            ' Limpar os campos na tabela "Registrar"
            ThisWorkbook.Sheets("Registrar").Range("B4, D4, E4, F4, G4, H4, I4, J4").ClearContents
    End If
    
    
    


End Sub
