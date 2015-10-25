Imports MySql.Data.MySqlClient
Public Class Form5
    Public MySqlCon As New MySqlConnection With {.ConnectionString = "Server=localhost;User=root;Pwd=tester;"}
    Public MySqlCmd As MySqlCommand
    Private Sub Show_AddStudents(sender As System.Object, e As System.EventArgs) Handles AddStudentButton.Click
        Form1.Show()
    End Sub

    Private Sub Show_SubmitQuestions(sender As System.Object, e As System.EventArgs) Handles SubmitQuestionButton.Click
        Form4.Show()
    End Sub

    Private Sub Show_StudentList(sender As System.Object, e As System.EventArgs) Handles StudentListButton.Click
        Form2.Show()
    End Sub

    Private Sub Initialise_Reader(sender As System.Object, e As System.EventArgs) Handles InitialiseReaderButton.Click
        Form6.Show()
    End Sub

    Private Sub Previous_Questions(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Form7.Show()
    End Sub


End Class