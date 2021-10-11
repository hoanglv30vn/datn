27/9 --> 11/10: 
	+> PIC
		- nút nhấn B0 -> chọn id node (1-10) - tạm thời chỉ 2 node 1 và 2
		- đo nhiệt độ gửi UART ( T>27 gửi)
		- nhận UART hiển thị LCD, điều khiển LED
	+> TCP
		- chọn COM, tên node
		- TCP server: nhận TCP gửi UART(GW), nhận UART gửi TCP tới mọi client
		- TCP client: nhận UART(NODE) gửi TCP(server), nhận TCP gửi UART.
	+> GATEWAY
		- chọn COM, baudrate
		- nhận UART, hiển thị, phân tích id, gửi firebase.
		- lắng nghe firebase, gửi uart tới tất cả các node.