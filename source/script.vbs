dim app
set app = CreateObject("KKE.Application")
dim array(9), index, s
array(0) = 1
array(1) = 10
array(2) = 3
array(3) = 2
array(4) = 5
array(5) = 7
array(6) = 3
array(7) = 7
array(8) = 9

' array = Array(1,10,3,2,5,7,3,7,9)

' for each index in array
'      Wscript.Echo index
' next
 
' MsgBox s

' Call app.SetMatrix(1, 10, 3, 2, 5, 7, 3, 7, 9, 3, 3)

Call app.SetMatrixByNum(3, 3, 9)

