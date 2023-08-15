// Nome do arquivo: mainwindow.cpp
// Autor: Pedro Emanuel Silva Miranda
// Data: 14/08/2023
// Descrição: Este é um programa de calculadora simples que realiza operações matemáticas básicas.
//            Note que nessa nova atualização acrescentei um "Tratamento de Exceção" para a divisão
//            por zero. Espero que aproveitem

/*OBS: apenas este código foi atualizado*/


#include "mainwindow.h"
#include "./ui_mainwindow.h"



// Rastreia valor atual para calcular
double calculaValor = 0.0;

// Define qual o último botão algébrico selecionado
bool divAciona = false;
bool multipAciona = false;
bool somaAciona = false;
bool subtAciona = false;
bool porcentAciona = false;

// Mantém falso quando não utilizado
bool limpaTAciona = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText( QString::number( calculaValor ));

    QPushButton *numButtons[10];    // Matriz que mantem a referencia dos botões de sinalização

    for (int i = 0; i < 10; ++i)
    {
        QString buttNome = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(buttNome);     // Busca pelo widget para obter os nomes

        // Chama o 'NumPressionado' quando algum botão numérico for pressionado
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressionado()));
    }

    // Faz uma referencia definitiva de cada método
    connect( ui->Button_divisao, SIGNAL(released()), this, SLOT(MatButtonPressionado()));
    connect( ui->Button_multiplicar, SIGNAL(released()), this, SLOT(MatButtonPressionado()));
    connect( ui->Button_soma, SIGNAL(released()), this, SLOT(MatButtonPressionado()));
    connect( ui->Button_subtracao, SIGNAL(released()), this, SLOT(MatButtonPressionado()));
    connect( ui->Button_porcentagem, SIGNAL(released()), this, SLOT(MatButtonPressionado()));

    connect( ui->Button_igual, SIGNAL(released()), this, SLOT(IgualButton()));

    connect( ui->Button_Limpar, SIGNAL(released()), this, SLOT(LimpaTela()));
    connect( ui->Button_mudaSinal, SIGNAL(released()), this, SLOT(MudaSinalNumero()));
}


// Destrutor
MainWindow::~MainWindow()
{
    delete ui;
}



// Realiza a operação matemática quando um botão numérico é pressionado.
void MainWindow::NumPressionado()
{
    QPushButton *button = (QPushButton *) sender();
    QString pegaValorBut = button->text();            // Obtém o número do botão que foi selecionado
    QString pegaValorDisplay = ui->Display->text();   // Obtém o valor no display

    if((pegaValorDisplay.toDouble() == 0) || (pegaValorDisplay.toDouble() == 0.0))  // Verifica se o valor atual do Display é zero (int ou double)
    {
        ui->Display->setText(pegaValorBut);                                         // Vai do Display até o valor do botão selecionado
    }
    else
    {                                                                   // Faz a coversão para expoente se atingir o máximo de 13 dígitos
        QString novoValor = pegaValorDisplay + pegaValorBut;
        double dblNovoValor = novoValor.toDouble();

        ui->Display->setText( QString::number( dblNovoValor, 'g', 13 ));
    }
}



// Realiza a operação matemática quando um botão de operador algébrico é pressionado.
void MainWindow::MatButtonPressionado()
{
    // Rastreamento dos botões clicados
    divAciona = false;
    multipAciona = false;
    somaAciona = false;
    subtAciona = false;
    porcentAciona = false;

    // Armazena o valor atual no Display para obter o texto de exibição para executar os métodos
    QString pegaValorDisplay = ui->Display->text();
    calculaValor = pegaValorDisplay.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString pegaValorBut = button->text();

    // Verifica se é o símbolo correto e se é um caso insensível maiúcula e minúscula para evitar possíveis falhas
    if( QString::compare(pegaValorBut, "/", Qt::CaseInsensitive) == 0 )
    {
        divAciona = true;
    }
    else
        if ( QString::compare(pegaValorBut, "X", Qt::CaseInsensitive) == 0 )
        {
            multipAciona = true;
        }
    else
        if ( QString::compare(pegaValorBut, "+", Qt::CaseInsensitive) == 0 )
        {
            somaAciona = true;
        }
    else
        if( QString::compare(pegaValorBut, "-", Qt::CaseInsensitive) == 0 )
        {
            subtAciona = true;
        }
    else
        if( QString::compare(pegaValorBut, "%", Qt::CaseInsensitive) == 0 )
        {
            porcentAciona = true;
        }

    ui->Display->setText("");       // Limpa a exibição para entrar em um novo número

}



// Calcula o resultado da expressão matemática.
void MainWindow::IgualButton()
{
    double solucao = 0.0;           // Mantém o cálculo para chamar a solução

    // Pega o valor da tela e converte para double para assim realizar o cálculo selecionado
    QString pegaValorDisplay = ui->Display->text();
    double dblValorDisplay = pegaValorDisplay.toDouble();

    if ( divAciona ||  multipAciona || somaAciona || subtAciona || porcentAciona )   // Verifica se o botão algébrico foi selecionado
    {

        if ( divAciona )
        {
            if (dblValorDisplay == 0.0)
            {
                ui->Display->setText("Divisão por Zero");
                return;     // Retorna para evitar cálculos incorretos
            }
            solucao = calculaValor / dblValorDisplay;       // Realize a operação de divisão normalmente, pois o denominador não é zero.
        }
        else
            if ( multipAciona )
            {
                solucao = calculaValor * dblValorDisplay;
            }
        else
            if ( somaAciona )
            {
                solucao = calculaValor + dblValorDisplay;
            }
        else
            if(subtAciona )
            {
                solucao = calculaValor - dblValorDisplay;
            }
        else
        {
            //dblValorDisplay = dblValorDisplay / 100;
            dblValorDisplay = 100;
            solucao = calculaValor / dblValorDisplay;
            //ui->Display->setText(QString::number( solucao / 100.0 ));
        }
    }

    ui->Display->setText( QString::number( solucao ));              // Retorna para a interface do usuário

}



// Limpa a tela da calculadora.
void MainWindow::LimpaTela()
{
    double solucao = 0.0;
    limpaTAciona = true;


    QString pegaValorDisplay = ui->Display->text();
    double dblValorDisplay = pegaValorDisplay.toDouble();


    if ( limpaTAciona )
    {
        solucao = 0.0;
    }

    ui->Display->setText( QString::number( solucao ));  // Retorna para a interface do usuário
}



// Inverte o sinal do número exibido na tela.
void MainWindow::MudaSinalNumero()
{
    // Armazena o valor atual no display para obter o texto de exibição para executar o método
    QString pegaValorDisplay = ui->Display->text();
    calculaValor = pegaValorDisplay.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString pegaValorBut = button->text();


    if( QString::compare(pegaValorBut, "+/-", Qt::CaseInsensitive) == 0 )
    {   // Método para mudar o sinal do número guardado
        double dblValorDisplay = pegaValorDisplay.toDouble();
        double dblSinalValorDisplay = -1 * dblValorDisplay;

        ui->Display->setText(QString::number(dblSinalValorDisplay));    // Mostrar na saída
    }
}








