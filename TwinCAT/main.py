import pyads
import math

# criando um objeto de conexão com PLC

# AMS Net ID -> id de qual PLC eu quero acessar
lays = "10.234.199.179.1.1"

# ip de quem está enviando
anna = "10.234.195.54.1.1"

# porta do serviço do PLC -> canal de comunicação
porta = pyads.PORT_TC3PLC1
plc = pyads.Connection(lays, porta, )
# Começando a conexão
plc.open()

x = int(input("Digite um número: "))

if math.isnan(x):
    Led += x
else:
    print("Escolha um valor válido!")
    
    
# fechando conexão
plc.close()
