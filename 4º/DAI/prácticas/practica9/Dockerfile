FROM python:3

ENV PYTHONUNBUFFERED=1

WORKDIR /app9
COPY . /app9/
# COPY requirements.txt /app9/

RUN pip install -r requirements.txt

CMD ["gunicorn", "-c", "config/gunicorn/conf.py", "--bind", ":8000", "--chdir", "app9", "mi_sitio_web.wsgi:application"]