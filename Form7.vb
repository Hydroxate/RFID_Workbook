Imports MySql.Data.MySqlClient
Public Class Form7

    Public MySqlCon As New MySqlConnection With {.ConnectionString = "Server=localhost;Database=Class2B;User=root;Pwd=tester;"}
    Public MySqlCmd As MySqlCommand
    Public todaysdate As String
    Public showdate As String
    Dim Answer As String
    Dim Question As String

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        Dim adapter As MySqlDataAdapter
        Dim ds As New DataSet
        Dim SQLStr As String
        DateTimePicker1.Format = DateTimePickerFormat.Custom
        DateTimePicker1.CustomFormat = "ddMMMyyyy"
        todaysdate = DateTimePicker1.Value.Date.ToString(DateTimePicker1.CustomFormat)

        SQLStr = "select * from Questions;"
        Try
            MySqlCon.Open()
                adapter = New MySqlDataAdapter(SQLStr, MySqlCon)
                adapter.Fill(ds)
                MySqlCon.Close()
                DataGridView1.DataSource = ds.Tables(0)
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try

    End Sub



    Private Sub MainMenuButton_Click(sender As System.Object, e As System.EventArgs) Handles MainMenuButton.Click
        Form5.Show()
        Form4.Close()
        Me.Close()

    End Sub

    Private Sub DateTimePicker1_ValueChanged(sender As System.Object, e As System.EventArgs) Handles DateTimePicker1.ValueChanged
        DateTimePicker1.Format = DateTimePickerFormat.Custom
        DateTimePicker1.CustomFormat = "ddMMMyyyy"
        todaysdate = DateTimePicker1.Value.Date.ToString(DateTimePicker1.CustomFormat)
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Dim strSQL As String
        Try
            strSQL = "CREATE TABLE IF NOT EXISTS " + todaysdate + "(Code varchar(16), Questions varchar(128) NOT NULL, Answers varchar(128) NOT NULL);"
            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strSQL, MySqlCon)
            MySqlCmd.ExecuteNonQuery()
            MySqlCon.Close()
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

        If Code1.Text.Trim.Length > 0 Then
            AddQ(Code1.Text.ToString)
        End If

        If Code2.Text.Trim.Length > 0 Then
            AddQ(Code2.Text.ToString)
        End If

        If Code3.Text.Trim.Length > 0 Then
            AddQ(Code3.Text.ToString)
        End If

        If Code4.Text.Trim.Length > 0 Then
            AddQ(Code4.Text.ToString)
        End If

        If Code5.Text.Trim.Length > 0 Then
            AddQ(Code5.Text.ToString)
        End If

        If Code6.Text.Trim.Length > 0 Then
            AddQ(Code6.Text.ToString)
        End If

        If Code7.Text.Trim.Length > 0 Then
            AddQ(Code7.Text.ToString)
        End If

        If Code8.Text.Trim.Length > 0 Then
            AddQ(Code8.Text.ToString)
        End If

        If Code9.Text.Trim.Length > 0 Then
            AddQ(Code9.Text.ToString)
        End If

        If Code10.Text.Trim.Length > 0 Then
            AddQ(Code10.Text.ToString)
        End If

        If Code11.Text.Trim.Length > 0 Then
            AddQ(Code11.Text.ToString)
        End If

        If Code12.Text.Trim.Length > 0 Then
            AddQ(Code12.Text.ToString)
        End If

        MsgBox("Questions Submitted")
    End Sub

    Public Sub AddQ(Code As String)
        Dim strInsert As String
        Try
            MySqlCon.Close()
            Dim strFind As String = "SELECT Questions, Answers FROM  Questions WHERE Code = '" + Code + "';"
            MySqlCon.Open()
            MySqlCmd = New MySqlCommand(strFind, MySqlCon)

            Dim reader = MySqlCmd.ExecuteReader()
            While reader.Read()
                Question = reader(0).ToString()
                Answer = reader(1).ToString()

            End While
            MySqlCon.Close()
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

        Try
            strInsert = "INSERT INTO " + todaysdate + "(Code, Questions, Answers)" & _
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

    Private Sub Button3_Click(sender As System.Object, e As System.EventArgs) Handles Button3.Click
        Dim adapter As MySqlDataAdapter
        Dim ds As New DataSet
        Dim SQLStr As String
        DateTimePicker2.Format = DateTimePickerFormat.Custom
        DateTimePicker2.CustomFormat = "ddMMMyyyy"
        showdate = DateTimePicker2.Value.Date.ToString(DateTimePicker2.CustomFormat)

        SQLStr = "select * from " + showdate + ";"
        Try
            MySqlCon.Open()
            adapter = New MySqlDataAdapter(SQLStr, MySqlCon)
            adapter.Fill(ds)
            MySqlCon.Close()
            DataGridView1.DataSource = ds.Tables(0)
        Catch ex As Exception
            MsgBox("No work set for selected date")
        End Try
    End Sub

End Class