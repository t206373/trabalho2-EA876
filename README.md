# EA876 - Trabalho 2

**Alunos**

Augusto Lourenço de Faria  **RA:**194447
Tony Tian Rui Li           **RA:**206373

**Descrição**

O projeto tem o intuito de avaliar a aplicação do filtro blur em diferentes imagens de 3 modos diferentes, com uma única linha de execução, process e threads, colhendo resultados experimentais e avaliativos.

Foi usada a linaguagem C em todo o projeto, e avaliado 50 vezes para cada modo de aplicação, os resultados se encontram no diretório 'doc'



**Instruções para teste**
Caso queira aplicar blur em outra imagem, é so alterar nos códigos:
-main.c: linhas 21,22 e 56
-main_process.c: linhas 56 e 96
-main_thread.c: linhas 77 e 117
Trocar joker.jpg, encontrado no diretório 'data' pelo nome da imagem que deseja filtrar nas linhas correspondentes ao abrir_imagem();
Renomear as saídas das linhas correspondentes ao salvar_imagem();
Após salvar os códigos, usar comando make test para compilar e executar os programas no diretório raiz.

**Instrução para cronometrar o programas N vezes**

for i in $(seq 1 N);
do
	$program env time --format="main gastou %es" ./main >out.txt
	$program env time --format="main_process gastou %es" ./main_process >out.txt
	$program env time --format="main_thread gastou %es" ./main_thread >out.txt
	rm out.txt
done

**Recomendações**

Substituir o test.sh por código acima, colocando a quantidade de veses que desejar no lugar do N.
Recomenda-se que faça o loop de um programa por vez, para isso deixe os outros programas comentados adicionando # no início
