import pyads
import time


# criando um objeto de conexão com PLC

# AMS Net ID -> id de qual PLC eu quero acessar

anna = "192.168.56.1.1.1"

# porta do serviço do PLC -> canal de comunicação
porta = pyads.PORT_TC3PLC1
plc = pyads.Connection(anna, porta)

plc.open()

# ITERANDO VARIÁVEL 
# plc.write_by_name("GVL.tempo", 1)

posicao = [0, 1, 2, 1, 3, 4, 3, 0]
index = 0

robotStatus = plc.read_by_name("GVL.robotStatus") # Destino -> 1 | Rodando -> 0

while True:
    if robotStatus == 0:
        if index >= len(posicao) - 1 or index < 0:
            index = 0
        index += 1

    plc.write_by_name("GVL.position", posicao[index])

    if index == 0 or index == 4:
        plc.write_by_name("GVL.gripperStatus", 0) 
    else:
        plc.write_by_name("GVL.gripperStatus", 1) 








# plc.write_by_name("GVL.position", 0)
# plc.write_by_name("GVL.gripperStatus", 0)  
# plc.write_by_name("GVL.robotStatus", 1)

# for i in posicao:
  
#     if(lastPosition != posicao[i]):
#         plc.write_by_name("GVL.robotStatus", 0)
#         plc.write_by_name("GVL.position", i)  
#         lastPosition = posicao[i]
    
    
        
#     if (i == posicao[2]):
#         plc.write_by_name("GVL.gripperStatus", 1)  
#     if(i == posicao[5]):
#         plc.write_by_name("GVL.gripperStatus", 0)  
        
plc.close()


# garra = [0, 0, 0, 1, 1, 1, 0, 0]


