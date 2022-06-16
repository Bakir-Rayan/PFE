import qrcode 

data=["start","blue_zone","yellow_zone"]
img_name=["start.png","blue_zone.png", "yellow_zone.png"]
for d,n in zip(data,img_name):
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
    )
    qr.add_data(d)
    qr.make(fit=True)
    img = qr.make_image(fill_color="black", back_color="white")
    img.save(f"./qrcodes/{n}")
    print("saved")