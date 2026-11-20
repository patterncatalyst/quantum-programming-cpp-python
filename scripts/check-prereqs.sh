#!/usr/bin/env bash
# Checks the host prerequisites for Quantum Programming in C++ and Python.
# The toolchains themselves live in containers; the host needs only Docker,
# the Compose plugin, and git. uv is optional, for fast local Python iteration.
set -euo pipefail

missing=0

check() {
    local cmd="$1" hint="$2"
    if command -v "$cmd" >/dev/null 2>&1; then
        printf 'ok:      %s (%s)\n' "$cmd" "$("$cmd" --version 2>&1 | head -1)"
    else
        printf 'MISSING: %s — %s\n' "$cmd" "$hint"
        missing=1
    fi
}

echo "Checking host prerequisites..."
check docker "install Docker Engine: https://docs.docker.com/engine/install/fedora/"
check git "dnf install git"

if docker compose version >/dev/null 2>&1; then
    printf 'ok:      docker compose (%s)\n' "$(docker compose version --short 2>/dev/null)"
else
    printf 'MISSING: docker compose plugin — install docker-compose-plugin\n'
    missing=1
fi

if command -v uv >/dev/null 2>&1; then
    printf 'ok:      uv (%s) [optional, local Python dev]\n' "$(uv --version 2>&1)"
else
    printf 'note:    uv not found [optional; the container provides Python 3.14]\n'
fi

if [ "$missing" -eq 0 ]; then
    echo "All required prerequisites are present."
else
    echo "Some required prerequisites are missing (see above)."
    exit 1
fi
