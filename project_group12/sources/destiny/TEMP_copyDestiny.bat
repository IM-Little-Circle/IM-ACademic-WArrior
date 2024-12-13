@echo on
REM Copy destiny3.txt to destiny4.txt through destiny20.txt

for /L %%N in (4,1,20) do (
    copy destiny_template.txt "D:\Documents\學習\26_台大資料\111_2024F\IM1001_程式設計\期末專案\2024f-pd-zhuan-an\sources\destiny\destiny%%N.txt"
)

echo All destiny files copied successfully.
pause