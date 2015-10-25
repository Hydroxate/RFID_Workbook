Imports System
Imports System.Collections.Generic
Imports System.Text
Imports System.ComponentModel
Imports System.Data
Imports System.Linq
Imports System.Drawing
Imports System.Windows.Forms
Imports MySql.Data.MySqlClient

Public Class Form2
    Public MySqlCon As New MySqlConnection With {.ConnectionString = "Server=localhost;Database=Class2B;User=root;Pwd=tester;"}

    Private Sub Populate_List(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        Dim adapter As MySqlDataAdapter
        Dim ds As New DataSet
        Dim SQLStr As String
        SQLStr = "select ID_Number, Last_Name, First_Name, Card_UID from studentlist;"
        Try
            MySqlCon.Open()
            adapter = New MySqlDataAdapter(SQLStr, MySqlCon)
            adapter.Fill(ds)
            DataGridView1.DataSource = ds.Tables(0)
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try
    End Sub


End Class