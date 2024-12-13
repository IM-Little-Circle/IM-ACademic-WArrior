@echo on
REM Copy destiny3.txt to destiny4.txt through destiny20.txt

for /L %%N in (2,1,20) do (
    copy chance_template.txt "chance%%N.txt"
)

echo All Chance files copied successfully.
pause