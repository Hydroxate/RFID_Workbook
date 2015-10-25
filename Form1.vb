Imports System
Imports System.IO.Ports
Imports MySql.Data.MySqlClient

Public Class Form1
    Public MySqlCon As New MySqlConnection With {.ConnectionString = "Server=localhost;Database=Class2B;User=root;Pwd=tester;"}
    Public MySqlCmd As MySqlCommand
    Delegate Sub myMethodDelegate(ByVal [text] As String)
    Dim myD1 As New myMethodDelegate(AddressOf ShowCardUID)
    Public Property Newline As String
    Dim data As String
    Dim CardUID As String
    Dim Str(12) As String
    Dim I As Integer

    Public Function HasConnection() As Boolean
        Try
            MySqlCon.Open()

            MySqlCon.Close()
            Return True
        Catch ex As Exception
            MsgBox(ex.Message)
            Return False
        End Try
    End Function

    Public Sub AddStudent(IDNumber As Integer, Lastname As String, FirstName As String, CardUID As String)

        HasConnection()
        Try
            Dim strSQL As String = "Create Table If Not Exists Studentlist(ID_Number int(8) NOT NULL, Last_Name varchar(16) NOT NULL, First_Name varchar(16) NOT NULL, Card_UID varchar(16) NOT NULL);"
            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strSQL, MySqlCon)
            MySqlCmd.ExecuteNonQuery()
            MySqlCon.Close()
        Catch
            MsgBox(" Could not create table", MsgBoxStyle.Critical)
        End Try

        Try
            Dim strInsert As String = "Insert Into Studentlist(ID_Number, Last_Name, First_Name, Card_UID)" & _
                                      "VALUES (" & _
                                      "'" & IDNumber & "', '" & Lastname & "', '" & FirstName & "', '" & CardUID & "');"

            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strInsert, MySqlCon)
            MySqlCmd.ExecuteNonQuery()
            MySqlCon.Close()
        Catch ex As Exception
            MsgBox(ex.Message)

        End Try

    End Sub

    Private Sub Button_Submit_Click(sender As System.Object, e As System.EventArgs) Handles Button_Submit.Click

        AddStudent(TextBox_STUDENTID.Text, TextBox_SURNAME.Text, TextBox_FIRSTNAME.Text, TextBox1.Text)
    End Sub

    Private Sub Button_Student_List_Click(sender As System.Object, e As System.EventArgs) Handles Button_Student_List.Click
        Form2.Show()
    End Sub

    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        Form5.Show()
    End Sub


    Private Sub ShowCardUID(ByVal myString As String)
         If SerialPort1.IsOpen Then
            SerialPort1.BaudRate = 9600
            If TextBox1.Text = String.Empty Then
                If Str(0).Contains("Card UID: ") Then
                    CardUID = Replace(Str(0), "Card UID: ", "")
                End If
                TextBox1.Text = CardUID
            End If
        End If
    End Sub

    Public Delegate Sub myDelegate()

    Private Sub SerialPort_DataReceived(ByVal sender As Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived

        While SerialPort1.IsOpen = True
            Try
                I = 0
                SerialPort1.NewLine = "Block 3"
                Str(0) = SerialPort1.ReadLine()
                Invoke(myD1, Str(0))

                'TextBox1.AppendText(" End of Current Card Data 3")
                SerialPort1.NewLine = "Block 4"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 4")
                SerialPort1.NewLine = "Block 5"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 5")
                SerialPort1.NewLine = "Block 6"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 6")
                SerialPort1.NewLine = "Block 7"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 7")
                SerialPort1.NewLine = "Block 8"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 8")
                SerialPort1.NewLine = "Block 9"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 9")
                SerialPort1.NewLine = "Block 10"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 10")
                SerialPort1.NewLine = "Block 11"
                Str(I) = SerialPort1.ReadLine()

                I += 1

                'TextBox1.AppendText(" End of Current Card Data 11")
                SerialPort1.NewLine = "Block 12"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 12")
                SerialPort1.NewLine = "Block 13"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 13")
                SerialPort1.NewLine = "Block 14"
                Str(I) = SerialPort1.ReadLine()
                I += 1

                'TextBox1.AppendText(" End of Current Card Data 14")
                SerialPort1.NewLine = "END"
                Str(I) = SerialPort1.ReadLine()

                I = 0

            Catch ex As Exception
                MsgBox(ex.Message)
            End Try
        End While

    End Sub


    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click

        If SerialPort1.IsOpen = False Then
            SerialPort1.Open()
            SerialPort1.DiscardInBuffer()
            SerialPort1.BaudRate = 9600
            SerialPort1.DataBits = 8
            SerialPort1.Parity = Parity.None
            SerialPort1.StopBits = StopBits.One
            SerialPort1.Handshake = Handshake.None
            SerialPort1.Encoding = System.Text.Encoding.Default 'very important!
        Else
            SerialPort1.Close()
            TextBox1.Clear()
        End If

    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        SerialPort1.Close()
        Me.Close()
    End Sub
End Class
