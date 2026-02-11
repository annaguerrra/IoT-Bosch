import pyads
import time


# criando um objeto de conexão com PLC

# AMS Net ID -> id de qual PLC eu quero acessar
malo = "10.234.198.62.1.1"
ipMalo = "10.234.199.183"
ipAnna = "10.234.195.79"
seg = 1
# ip de quem está enviando
anna = "10.234.195.79.1.1"

# porta do serviço do PLC -> canal de comunicação
porta = pyads.PORT_TC3PLC1
plc = pyads.Connection(anna, porta, ipAnna)

plc.open()

posicao = [0, 1, 2, 1, 3, 4, 3, 0]
garra = [0, 0, 0, 1, 1, 1, 0, 0]

status = plc.read_by_name("GVL.RobotStatus")
lastPosition = plc.read_by_name("GVL.position")
        
plc.write_by_name("GVL.position", 0)
plc.write_by_name("GVL.gripperStatus", 0)  
plc.write_by_name("GVL.position", 1)

      
position = posicao[0]

if(position != lastPosition ):
    
    
plc.close()




# ITERANDO VARIÁVEL 
# plc.write_by_name("GVL.tempo", 1)

# CONTROLANDO ROBÔ
# não fazer movimento em diagonal
    # POSITION          0 -> Home | 1 -> P1 [...]
    # GRIPPER_STATUS    0 -> Abre | 1 -> Fecha
   
# plc.write_by_name("GVL.position", 2)     
# plc.write_by_name("GVL.gripperStatus", 1)      
# plc.write_by_name("GVL.position", 1)            
# plc.write_by_name("GVL.position", 3)            
# plc.write_by_name("GVL.position", 4)            
# plc.write_by_name("GVL.gripperStatus", 0)            
# plc.write_by_name("GVL.position", 3)         
# plc.write_by_name("GVL.position", 0)
