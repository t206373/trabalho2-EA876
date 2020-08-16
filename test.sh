# Script para testes de unidade automaticos

echo "Aplicando blur com main.c"
$program ./main >out.txt
echo "Imagem -out gerada."

echo "Aplicando blur com main_process.c"
$program ./main_process >out.txt
echo "Imagem -process-out gerada."

echo "Aplicando blur com main_thread.c"
$program ./main_thread >out.txt
echo "Imagem -thread-out gerada."

rm out.txt