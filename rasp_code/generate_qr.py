import qrcode 

data=["BLUE ZONE", "RED ZONE", "YELLOW ZONE"]
img_name=["blue_zone.png", "red_zone.png", "yellow_zone.png"]
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
    img.save(n)
    print("saved")