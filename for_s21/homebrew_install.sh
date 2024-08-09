#!/bin/bash
cd /opt/goinfre/$USER
git clone https://github.com/Homebrew/brew homebrew
cd $HOME
if [ ! -f ".zprofile" ]; then
touch .zprofile
fi
echo 'function brsw {' >> .zprofile
echo 'eval "$(/opt/goinfre/$USER/homebrew/bin/brew shellenv)"' >> .zprofile
echo 'brew update --force --quiet' >> .zprofile
echo 'chmod -R go-w "$(brew --prefix)/share/zsh"' >> .zprofile
echo '}' >> .zprofile

