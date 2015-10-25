Imports MySql.Data.MySqlClient
Public Class Form4

    Public MySqlCon As New MySqlConnection With {.ConnectionString = "Server=localhost;Database=Class2B;User=root;Pwd=tester;"}
    Public MySqlCmd As MySqlCommand
    Public todaysdate As String

    Private Sub Form4_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load

        Form5.Show()
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click

        Dim strSQL As String
        Try
            strSQL = "CREATE TABLE IF NOT EXISTS Questions(Code varchar(16) NOT NULL, Questions varchar(128) NOT NULL,Answers varchar(48) NOT NULL);"
            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strSQL, MySqlCon)
            MySqlCmd.ExecuteNonQuery()
            MySqlCon.Close()
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

        Try
            If (Code1.Text.Trim.Length > 0) And (Question1.Text.Trim.Length > 0) And (Answer1.Text.Trim.Length > 0) Then
                AddQA(Code1.Text.ToString, Question1.Text.ToString, Answer1.Text.ToString)
            End If
            If (Code2.Text.Trim.Length > 0) And (Question2.Text.Trim.Length > 0) And (Answer2.Text.Trim.Length > 0) Then
                AddQA(Code2.Text.ToString, Question2.Text.ToString, Answer2.Text.ToString)
            End If
            If (Code3.Text.Trim.Length > 0) And (Question3.Text.Trim.Length > 0) And (Answer3.Text.Trim.Length > 0) Then
                AddQA(Code3.Text.ToString, Question3.Text.ToString, Answer3.Text.ToString)
            End If
            If (Code4.Text.Trim.Length > 0) And (Question4.Text.Trim.Length > 0) And (Answer4.Text.Trim.Length > 0) Then
                AddQA(Code4.Text.ToString, Question4.Text.ToString, Answer4.Text.ToString)
            End If
            If (Code5.Text.Trim.Length > 0) And (Question5.Text.Trim.Length > 0) And (Answer5.Text.Trim.Length > 0) Then
                AddQA(Code5.Text.ToString, Question5.Text.ToString, Answer5.Text.ToString)
            End If
            If (Code6.Text.Trim.Length > 0) And (Question6.Text.Trim.Length > 0) And (Answer6.Text.Trim.Length > 0) Then
                AddQA(Code6.Text.ToString, Question6.Text.ToString, Answer6.Text.ToString)
            End If
            If (Code7.Text.Trim.Length > 0) And (Question7.Text.Trim.Length > 0) And (Answer7.Text.Trim.Length > 0) Then
                AddQA(Code7.Text.ToString, Question7.Text.ToString, Answer7.Text.ToString)
            End If
            If (Code8.Text.Trim.Length > 0) And (Question8.Text.Trim.Length > 0) And (Answer8.Text.Trim.Length > 0) Then
                AddQA(Code8.Text.ToString, Question8.Text.ToString, Answer8.Text.ToString)
            End If
            If (Code9.Text.Trim.Length > 0) And (Question9.Text.Trim.Length > 0) And (Answer9.Text.Trim.Length > 0) Then
                AddQA(Code9.Text.ToString, Question9.Text.ToString, Answer9.Text.ToString)
            End If
            If (Code10.Text.Trim.Length > 0) And (Question10.Text.Trim.Length > 0) And (Answer10.Text.Trim.Length > 0) Then
                AddQA(Code10.Text.ToString, Question10.Text.ToString, Answer10.Text.ToString)
            End If
            If (Code11.Text.Trim.Length > 0) And (Question11.Text.Trim.Length > 0) And (Answer11.Text.Trim.Length > 0) Then
                AddQA(Code11.Text.ToString, Question11.Text.ToString, Answer11.Text.ToString)
            End If
            If (Code12.Text.Trim.Length > 0) And (Question12.Text.Trim.Length > 0) And (Answer12.Text.Trim.Length > 0) Then
                AddQA(Code12.Text.ToString, Question12.Text.ToString, Answer12.Text.ToString)
            End If
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

    End Sub

    Public Sub AddQA(Code As String, Question As String, Answer As String)
        Dim strInsert As String

        Try
            strInsert = "INSERT INTO Questions(Code, Questions, Answers)" & _
                                         "VALUES (" & _
                                         "'" & Code & "', '" & Question & "', '" & Answer & "');"
            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strInsert, MySqlCon)
            MySqlCmd.ExecuteNonQuery()
            MySqlCon.Close()
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try


    End Sub


    Private Sub Label1_Click(sender As System.Object, e As System.EventArgs) Handles Label1.Click

    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Code1.Clear()
        Code2.Clear()
        Code3.Clear()
        Code4.Clear()
        Code5.Clear()
        Code6.Clear()
        Code7.Clear()
        Code8.Clear()
        Code9.Clear()
        Code10.Clear()
        Code11.Clear()
        Code12.Clear()
        Question1.Clear()
        Question2.Clear()
        Question3.Clear()
        Question4.Clear()
        Question5.Clear()
        Question6.Clear()
        Question7.Clear()
        Question8.Clear()
        Question9.Clear()
        Question10.Clear()
        Question11.Clear()
        Question12.Clear()
        Answer1.Clear()
        Answer2.Clear()
        Answer3.Clear()
        Answer4.Clear()
        Answer5.Clear()
        Answer6.Clear()
        Answer7.Clear()
        Answer8.Clear()
        Answer9.Clear()
        Answer10.Clear()
        Answer11.Clear()
        Answer12.Clear()
    End Sub
End Class