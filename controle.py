#########################################
#  Universidade Federal do Paraná
#  TADS - SEPT
#
#  Projeto de Automação Residencial
#
#  Equipe:
#  João Victor Alves da Maia
#  Marcos Antonio da Silva
#
#  Última alteração: 24/11/2018
#########################################
import serial
import time

porta = 'COM3'
velocidade = 9600
opcao = ''
relatorioTemperatura = []

#Configura e faz conexão serial
conexao = serial.Serial(porta, velocidade)

#Informações da conexão
print('::::::::::::::::::::::::::::')
print(' Conexão')
print('  - Status: ', conexao.isOpen())
print('  - Device: ', conexao.name)
print('  - Velocidade: ', conexao.baudrate)
print('::::::::::::::::::::::::::::')

while True:
    print('0 - Sair')
    print('1 - Acender Led')
    print('2 - Desligar Led')
    print('3 - Acionar Percianas')
    print('4 - Monitorar temperatura')
    
    opcao = input()
    
    if(opcao == '0'):
        break
    else:
        #Tratamento para opção de relatório de temperatura
        if(opcao == '4'):
            print('Iniciando monitoria da temperatura. Aguarde um instante...')
            for i in range(10):
                #Envia parametro para ler temperatura
                conexao.write(str(opcao).encode())
                #Captura retorno da leitura
                relatorioTemperatura.append(conexao.readline())
            #Printa os dados lidos
            #print(*relatorioTemperatura, sep = '\n')
            for x in range(len(relatorioTemperatura)):
                temp = str(relatorioTemperatura[x])
                print(temp.decode('utf-8'))
        else:
            #Envia parametro para o arduino
            conexao.write(str(opcao).encode())

#Finaliza conexão com porta serial
conexao.close()