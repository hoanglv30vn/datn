*******DATN_V1
27/9 --> 11/10: 
https://github.com/hoanglv30vn/datn
-[PIC] nút nhấn B0 -> chọn id node (1-10) 
-[PIC] tạm thời chỉ 2 node 1 và 2 - đo nhiệt độ gửi UART ( T>27 gửi) 
-[PIC] nhận UART hiển thị LCD, điều khiển LED 
-[TCP] chọn COM, tên node 
-[TCP] TCP server: nhận TCP gửi UART(GW), nhận UART gửi TCP tới mọi client 
-[TCP] TCP client: nhận UART(NODE) gửi TCP(server), nhận TCP gửi UART. 
-[GATEWAY] chọn COM, baudrate - nhận UART, hiển thị, phân tích id, gửi firebase. 
-[GATEWAY] lắng nghe firebase, gửi uart tới tất cả các node.


*******DATN_V2
27/10 -->
https://github.com/hoanglv30vn/datn_v2
