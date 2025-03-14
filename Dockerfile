FROM ubuntu:22.04

# Avoid timezone prompt during package installation
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Install essential build tools and development packages
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gcc \
    gdb \
    git \
    make \
    pkg-config \
    valgrind \
    vim \
    tmux \
    curl \
    zsh \
    && rm -rf /var/lib/apt/lists/*

# Set up a working directory
WORKDIR /app

# Copy all project files into the container
COPY . /app/

# Create a non-root user for better security
RUN useradd -m japostad && \
    chown -R japostad:japostad /app

# Switch to user
USER japostad
WORKDIR /home/japostad

# Clone the dotfiles repository
RUN git clone https://github.com/japostadan/dotfiles-devpod.git .dotfiles && \
    cd .dotfiles && \
    ln -sf ~/.dotfiles/.tmux.conf ~/.tmux.conf && \
    ln -sf ~/.dotfiles/.zshrc ~/.zshrc && \
    ln -sf ~/.dotfiles/.vimrc ~/.vimrc

USER root
RUN chsh -s /usr/bin/zsh japostad
USER japostad
# Set the working directory back to /app
WORKDIR /app

# Command to run when container starts (you can change this to your app or a shell)
CMD ["/bin/zsh"]
