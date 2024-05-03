import smtplib
import sys
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

recipient = sys.argv[1]
subject = sys.argv[2]
body = sys.argv[3]

# Configurer les informations SMTP
smtp_server = 'smtp.gmail.com'
port = 587
sender_email = 'moustachnia@gmail.com'
password = 'zzgn amhu grie isxc'

# Créer un e-mail
message = MIMEMultipart()
message['From'] = sender_email
message['To'] = recipient
message['Subject'] = subject
message.attach(MIMEText(body, 'plain'))

# Se connecter au serveur SMTP et envoyer l'e-mail
try:
    server = smtplib.SMTP(smtp_server, port)
    server.starttls()
    server.login(sender_email, password)
    server.sendmail(sender_email, recipient, message.as_string())
    print('E-mail sent successfully')
except Exception as e:
    print('Error sending e-mail:', str(e))
finally:
    server.quit()
