import pyads
import time

# criando um objeto de conexão com PLC

anna = "192.168.56.1.1.1"      # AMS Net ID -> id de qual PLC eu quero acessar
ipAnna = "10.234.195.79"        # ip de quem está enviando
seg = 2


porta = pyads.PORT_TC3PLC1      # porta do serviço do PLC -> canal de comunicação
plc = pyads.Connection(anna, porta)
plc.open()

# ITERANDO VARIÁVEL DO VIZINHO
# plc.write_by_name("GVL.tempo", 1)

# CONTROLANDO ROBÔ
# não fazer movimento em diagonal
    # POSITION          0 -> Home | 1 -> P1 [...]
    # GRIPPER_STATUS    0 -> Abre | 1 -> Fecha

plc.write_by_name("GVL.position", 0)        # posição 0 inicio
time.sleep(seg)
plc.write_by_name("GVL.gripperStatus", 0)  # abrindo garra
time.sleep(seg)
plc.write_by_name("GVL.position", 1)      # indo p P1
time.sleep(seg)
plc.write_by_name("GVL.position", 2)     # indo para P2
time.sleep(seg)
plc.write_by_name("GVL.gripperStatus", 1)      # fechando garra
time.sleep(seg)
plc.write_by_name("GVL.position", 1)            # subindo, voltando para P1
time.sleep(seg)
plc.write_by_name("GVL.position", 3)            # indo p P3
time.sleep(seg)
plc.write_by_name("GVL.position", 4)            # desço, indo p P4
time.sleep(seg)
plc.write_by_name("GVL.gripperStatus", 0)            
time.sleep(seg)
plc.write_by_name("GVL.position", 3)         # volto p P3
time.sleep(seg)
plc.write_by_name("GVL.position", 0)        # volto p ponto inicial

plc.close()




