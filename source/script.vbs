dim app
set app = CreateObject("KKE.Application")

Wscript.Echo app.AddMatrixNum

dim test_matrix1(2,2)
dim test_matrix2(2,2)

app.AddMatrixNum(0)

Wscript.Echo test_matrix2(1,1)
