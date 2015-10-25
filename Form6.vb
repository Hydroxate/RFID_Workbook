Imports System
Imports System.IO.Ports
Imports MySql.Data.MySqlClient



Public Class Form6
    Public Writedate As String
    Public Readdate As String
    Private readBuffer As String = String.Empty
    Dim str(0 To 12) As String
    Dim question(0 To 11) As String
    Dim question_hex(0 To 11) As String
    Dim answer(0 To 11) As String
    Dim answer_hex(0 To 11) As String
    Delegate Sub myMethodDelegate1(ByVal [text] As String)
    Delegate Sub myMethodDelegate2(ByVal [text] As String)
    Delegate Sub myMethodDelegate3(ByVal [text] As String)
    Dim myD1 As New myMethodDelegate1(AddressOf ShowSerialData)
    Dim myD2 As New myMethodDelegate2(AddressOf Hex_to_Ascii)
    Dim myD3 As New myMethodDelegate3(AddressOf Ascii_to_Hex)
    Dim ReaderMode As Char
    Private CardID As String
    Private StudentName As String
    Public Property Newline As String
    Public i As Integer
    Public g As Integer = 0
    Public n As Integer = 0


    Public MySqlCon As New MySqlConnection With {.ConnectionString = "Server=localhost;Database=Class2B;User=root;Pwd=tester;"}
    Public MySqlCmd As MySqlCommand

    Private Sub Form6_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        DateTimePicker2.Format = DateTimePickerFormat.Custom
        DateTimePicker2.CustomFormat = "ddMMMyyyy"
        Readdate = DateTimePicker2.Value.Date.ToString(DateTimePicker2.CustomFormat)
        DateTimePicker1.Format = DateTimePickerFormat.Custom
        DateTimePicker1.CustomFormat = "ddMMMyyyy"
        Writedate = DateTimePicker1.Value.Date.ToString(DateTimePicker1.CustomFormat)
    End Sub

    Private Sub StartReadButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles StartReadButton.Click
        If SerialPort1.IsOpen = True Then
            SerialPort1.DiscardInBuffer()
            SerialPort1.Close()
        End If

        SerialPort1.Open()
        RichTextBox2.Clear()
        RichTextBox2.AppendText(SerialPort1.PortName)

        If SerialPort1.IsOpen = False Then
            SerialPort1.Open()
            SerialPort1.BaudRate = 9600
            SerialPort1.DataBits = 8
            SerialPort1.Parity = Parity.None
            SerialPort1.StopBits = StopBits.One
            SerialPort1.Handshake = Handshake.None
            SerialPort1.Encoding = System.Text.Encoding.Default 'very important!

            TextBox1.AppendText("Port Open")
            TextBox1.AppendText(vbNewLine)
        End If
        ReaderMode = "r"
        SerialPort1.Write("r")
    End Sub

    Private Sub ShowSerialData(ByVal myString As String)
        If SerialPort1.IsOpen Then
            SerialPort1.BaudRate = 9600
            If TextBox2.Text = String.Empty Then
                If str(0).Contains("Card UID: ") Then
                    CardID = Replace(str(0), "Card UID: ", "")
                End If
                TextBox2.AppendText(CardID)
            End If

            If i = 0 And TextBox2.Text = CardID Then
                TextBox2.Text = String.Empty
            End If
            Try
                TextBox1.AppendText(myString)
                TextBox1.ScrollToCaret()
            Catch
                MsgBox("Connection Closed")
            End Try
        End If

    End Sub

    Public Delegate Sub myDelegate1()
    Public Delegate Sub myDelegate2()
    Public Delegate Sub myDelegate3()

    Private Sub SerialPort_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived

        While SerialPort1.IsOpen = True
            If ReaderMode = "r" Then
                Try
                    i = 0
                    SerialPort1.NewLine = "Block 3"
                    str(i) = SerialPort1.ReadLine()
                    'str(i) = Replace(str(i), " ", "")
                    Invoke(myD1, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 3")
                    SerialPort1.NewLine = "Block 4"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 4")
                    SerialPort1.NewLine = "Block 5"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 5")
                    SerialPort1.NewLine = "Block 6"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 6")
                    SerialPort1.NewLine = "Block 7"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 7")
                    SerialPort1.NewLine = "Block 8"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 8")
                    SerialPort1.NewLine = "Block 9"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 9")
                    SerialPort1.NewLine = "Block 10"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 10")
                    SerialPort1.NewLine = "Block 11"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 11")
                    SerialPort1.NewLine = "Block 12"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 12")
                    SerialPort1.NewLine = "Block 13"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 13")
                    SerialPort1.NewLine = "Block 14"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    i += 1

                    'TextBox1.AppendText(" End of Current Card Data 14")
                    SerialPort1.NewLine = "END"
                    str(i) = SerialPort1.ReadLine()
                    Invoke(myD1, str(i))
                    Invoke(myD2, str(i))
                    Store_Answers()
                    i = 0

                    SerialPort1.Write("r")

                Catch
                    MsgBox("Connection Closed")
                End Try
            ElseIf ReaderMode = "w" Then

            End If
        End While
    End Sub

    Private Sub Hex_to_Ascii(ByVal myString1 As String)
        myString1 = Replace(myString1, " ", "")
        myString1 = Replace(myString1, vbCrLf, "")
        Try
            For j = 0 To myString1.Length - 1 Step 2
                Dim k As String = myString1.Substring(j, 2)
                answer(i - 1) += System.Convert.ToChar(System.Convert.ToUInt32(k, 16)).ToString()
                TextBox3.AppendText(answer(i - 1))
                TextBox3.ScrollToCaret()

            Next
        Catch
            MsgBox("Card Read Error, Try Again")
        End Try

    End Sub

    Private Sub Ascii_to_Hex(ByVal myString2 As String)
        Try

            Dim byteArray() As Byte
            Dim hexNumbers As System.Text.StringBuilder = New System.Text.StringBuilder
            byteArray = System.Text.ASCIIEncoding.ASCII.GetBytes(myString2)
            For l As Integer = 0 To byteArray.Length - 1
                hexNumbers.Append(byteArray(l).ToString("X2"))
            Next

           
            question_hex(g) = hexNumbers.ToString


            TextBox3.AppendText(question_hex(g))
            TextBox3.AppendText(vbCr)
            hexNumbers.Clear()

        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

    End Sub

    Private Sub Store_Answers()
        Try
            MySqlCon.Close()
            Dim strFind As String = "SELECT ID_Number FROM  Studentlist WHERE Card_UID = '" + CardID + "';"
            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strFind, MySqlCon)

            Dim reader = MySqlCmd.ExecuteReader()
            While reader.Read()
                StudentName = reader(0).ToString()
            End While
            MySqlCon.Close()
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

        Try
            Dim strSQL As String = "ALTER TABLE " + Readdate + " ADD " + StudentName + " varchar(32);"
            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strSQL, MySqlCon)
            MySqlCmd.ExecuteNonQuery()
            MySqlCon.Close()
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

        Try
            For I As Integer = 1 To 12
                If question(I - 1) = String.Empty Then
                    question(I - 1) = "NO ANSWER GIVEN"
                End If
                Dim strInsert As String = "INSERT INTO " + Readdate + "(" + StudentName + ")" & _
                                         "VALUES (" & _
                                         "'" & question(I - 1) & "');"
                MySqlCon.Open()
                MySqlCmd = New MySqlCommand(strInsert, MySqlCon)
                MySqlCmd.ExecuteNonQuery()
                MySqlCon.Close()
            Next
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

    End Sub

    Private Sub StopReadButton_Click(sender As System.Object, e As System.EventArgs) Handles StopReadButton.Click

        If SerialPort1.IsOpen = True Then
            SerialPort1.DiscardInBuffer()
            SerialPort1.Close()
            TextBox1.AppendText(vbNewLine)
            TextBox1.AppendText("Port Closed")
            RichTextBox2.Clear()
            TextBox2.Clear()
        End If

    End Sub

    Private Sub StopWriteButton_Click(sender As System.Object, e As System.EventArgs) Handles StopWriteButton.Click


        SerialPort1.DiscardOutBuffer()
        SerialPort1.Close()
        TextBox1.AppendText(vbNewLine)
        TextBox1.AppendText("Port Closed")
        RichTextBox2.Clear()
        TextBox2.Clear()


    End Sub

    Private Sub DateTimePicker1_ValueChanged(sender As System.Object, e As System.EventArgs) Handles DateTimePicker1.ValueChanged

        DateTimePicker1.Format = DateTimePickerFormat.Custom
        DateTimePicker1.CustomFormat = "ddMMMyyyy"
        Writedate = DateTimePicker1.Value.Date.ToString(DateTimePicker1.CustomFormat)

    End Sub

    Private Sub DateTimePicker2_ValueChanged(sender As System.Object, e As System.EventArgs) Handles DateTimePicker2.ValueChanged

        DateTimePicker2.Format = DateTimePickerFormat.Custom
        DateTimePicker2.CustomFormat = "ddMMMyyyy"
        Readdate = DateTimePicker2.Value.Date.ToString(DateTimePicker2.CustomFormat)

    End Sub

    Private Sub ClearButton_Click(sender As System.Object, e As System.EventArgs) Handles ClearButton.Click
        TextBox1.Clear()
        TextBox3.Clear()
    End Sub

    Private Sub StartWriteButton_Click(sender As System.Object, e As System.EventArgs) Handles StartWriteButton.Click
        Dim WriteStr As String = "select Code from " + Writedate + ";"
        Try
            MySqlCon.Open()
        Catch
        End Try
        MySqlCmd = New MySqlCommand(WriteStr, MySqlCon)
        Dim reader = MySqlCmd.ExecuteReader()
        ReaderMode = "w"

        While reader.Read()

            question(g) = reader.GetString(0)
            Invoke(myD3, question(g))
            g += 1
        End While
        g = 0
        MySqlCon.Close()

        If SerialPort1.IsOpen = True Then
            SerialPort1.DiscardInBuffer()
            SerialPort1.Close()
        End If

        For n As Integer = 0 To 11
            If question_hex(n) = String.Empty Then
                question_hex(n) = "00000000000000000000000000000000"
            End If
        Next

        SerialPort1.Open()

        SerialPort1.DiscardInBuffer()
        RichTextBox2.Clear()
        RichTextBox2.AppendText(SerialPort1.PortName)

        If SerialPort1.IsOpen = False Then
            SerialPort1.Open()
            SerialPort1.BaudRate = 9600
            SerialPort1.DataBits = 8
            SerialPort1.Parity = Parity.None
            SerialPort1.StopBits = StopBits.One
            SerialPort1.Handshake = Handshake.None
            SerialPort1.Encoding = System.Text.Encoding.Default 'very important!

            TextBox1.AppendText("Port Open")
            TextBox1.AppendText(vbNewLine)
        End If

        While SerialPort1.IsOpen = True
            Try
                SerialPort1.Write("w")
                'SerialPort1.NewLine = "END"
                Dim incoming As String = SerialPort1.ReadLine

                For n As Integer = 0 To 11
                    'If incoming = "Ready" Then
                    SerialPort1.Write("w")
                    SerialPort1.Write(question_hex(n))
                    SerialPort1.DiscardOutBuffer()
                    TextBox1.AppendText(SerialPort1.ReadExisting)
                    'System.Threading.Thread.Sleep(100)
                    'End If
                Next

            Catch ex As Exception
                MsgBox(ex.Message)
            End Try
            n = 0
        End While


    End Sub

    Private Sub Label1_Click(sender As System.Object, e As System.EventArgs) Handles Label1.Click

    End Sub

    Private Sub ChangeFontToolStripMenuItem_Click(sender As System.Object, e As System.EventArgs)

    End Sub
End Class

