import pyads
import time

# criando um objeto de conexão com PLC

anna = "10.234.195.79.1.1"      # AMS Net ID -> id de qual PLC eu quero acessar
ipAnna = "10.234.195.79"        # ip de quem está enviando
seg = 1


porta = pyads.PORT_TC3PLC1      # porta do serviço do PLC -> canal de comunicação
plc = pyads.Connection(anna, porta, ipAnna)
plc.open()

# ITERANDO VARIÁVEL DO VIZINHO
# plc.write_by_name("GVL.tempo", 1)

# CONTROLANDO ROBÔ
# não fazer movimento em diagonal
    # POSITION          0 -> Home | 1 -> P1 [...]
    # GRIPPER_STATUS    0 -> Abre | 1 -> Fecha

plc.write_by_name("GVL.position", 0)
time.sleep(seg)
plc.write_by_name("GVL.gripperStatus", 0)  
time.sleep(seg)
plc.write_by_name("GVL.position", 1)      
time.sleep(seg)
plc.write_by_name("GVL.position", 2)     
time.sleep(seg)
plc.write_by_name("GVL.gripperStatus", 1)      
time.sleep(seg)
plc.write_by_name("GVL.position", 1)            
time.sleep(seg)
plc.write_by_name("GVL.position", 3)            
time.sleep(seg)
plc.write_by_name("GVL.position", 4)            
time.sleep(seg)
plc.write_by_name("GVL.gripperStatus", 0)            
time.sleep(seg)
plc.write_by_name("GVL.position", 3)         
time.sleep(seg)
plc.write_by_name("GVL.position", 0)

plc.close()




