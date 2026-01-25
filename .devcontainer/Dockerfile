FROM registry.gitlab.com/musicscience37projects/docker/my-cpp-env-docker:clang21

USER root
# Install Google Chrome and pdftocairo (poppler-utils package).
RUN curl -fsSL https://dl.google.com/linux/linux_signing_key.pub \
    | gpg --dearmor -o /usr/share/keyrings/chrome-keyring.gpg && \
    echo "deb [arch=amd64 signed-by=/usr/share/keyrings/chrome-keyring.gpg] http://dl.google.com/linux/chrome/deb/ stable main" \
    | tee /etc/apt/sources.list.d/google-chrome.list && \
    apt-get update && \
    apt-get install -y google-chrome-stable poppler-utils && \
    apt-get autoremove -y && \
    apt-get autoclean && \
    rm -r /var/lib/apt/lists/*

USER ubuntu
WORKDIR /home/ubuntu
