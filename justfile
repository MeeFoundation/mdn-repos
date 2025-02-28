set dotenv-load

_default:
  @ just --list --unsorted

# -- db setup (run once)

init-db:
  #!/bin/sh
  set -eu
  cd repos/mee-utils/scripts
  make -f dev.service.common.mk run_db_daemon
  
create-agent-service-db:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/services/agent_service
  make create_db
  
create-mdn-license-manager-db:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/mdn_license_manager
  make create_db
  
create-mee-user-manager-db:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/mee_user_manager
  make create_db
  
create-mee-provider-manager-db:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/mee_provider_manager
  make create_db
  
create-oidc-provider-db:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/oidc_provider
  make create_db

# -- mdn services

run-mdn-license-manager:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/mdn_license_manager
  cp .env.example .env
  make dev

run-mee-user-manager:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/mee_user_manager
  cp .env.example .env
  make dev

run-mee-provider-manager:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/mee_provider_manager
  cp .env.example .env
  make dev

run-oidc-provider:
  #!/bin/sh
  set -eu
  cd repos/mee-network-administration/services/oidc_provider
  cp .env.example .env
  make dev

# -- providers

# port 8010
run-demo-provider-oyt:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/services/agent_service
  cp .env.example .env
  export SERVER_PORT=8010
  make run_provider1

# port 8011
run-demo-provider-ua:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/services/agent_service
  cp .env.example .env
  export SERVER_PORT=8011
  make run_provider2

# -- web uis

run-untied-airlines-user-web-ui:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/examples/untied-airlines-user-web-ui
  # nvm use lts/jod
  cp .env.example .env
  pnpm install
  pnpm run astro dev

run-agent-sdk-user-web-ui-oyt:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/examples/agent-sdk-user-web-ui
  # nvm use lts/jod
  npm install
  npm run provider-oyt

run-agent-sdk-user-web-ui-ua:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/examples/agent-sdk-user-web-ui
  # nvm use lts/jod
  npm install
  npm run provider-ua

run-agent-sdk-provider-web-ui-oyt:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/examples/agent-sdk-provider-web-ui
  # nvm use lts/jod
  npm install
  npm run provider-oyt

run-agent-sdk-provider-web-ui-ua:
  #!/bin/sh
  set -eu
  cd repos/mee-network-provider/examples/agent-sdk-provider-web-ui
  # nvm use lts/jod
  npm install
  npm run provider-ua

# -- unified setup

setup-local-databases:
  #!/bin/sh
  set -eu
  just init-db
  until pg_isready -h localhost -p 5432; do
    echo "Waiting for PostgreSQL to become available..."
    sleep 1
  done
  just create-agent-service-db
  just create-mdn-license-manager-db
  just create-mee-user-manager-db
  just create-mee-provider-manager-db
  just create-oidc-provider-db

start-demo:
  #!/bin/sh
  set -eu
  #
  # Colors for prettier output
  GREEN='\033[0;32m'
  BLUE='\033[0;34m'
  NC='\033[0m' # No Color
  #
  # Function to start a service in a new tmux session
  start_service() {
      service_name=$1
      command=$2
      
      echo "Starting service ${BLUE}$service_name${NC}..."
      
      # Create a new tmux session running the command
      tmux new-session -d -s "$service_name" "$command"
      
      # Check if session was created successfully
      if tmux has-session -t "$service_name" 2>/dev/null; then
          echo -e "Service ${BLUE}$service_name${NC} started, tmux session: ${GREEN}$service_name${NC}"
          return 0
      else
          echo "Failed to start service $service_name"
          return 1
      fi
  }
  #
  # Start services
  echo "--- starting MDN services ---"
  start_service "mdn-license-manager" "just run-mdn-license-manager"
  start_service "mee-user-manager" "just run-mee-user-manager"
  start_service "mee-provider-manager" "just run-mee-provider-manager"
  start_service "oidc-provider" "just run-oidc-provider"
  echo "--- starting provider nodes ---"
  start_service "provider-oyt" "just run-demo-provider-oyt"
  start_service "provider-ua" "just run-demo-provider-ua"
  echo "--- starting web UIs ---"
  start_service "untied-airlines-user-web-ui" "just run-untied-airlines-user-web-ui"
  start_service "agent-sdk-user-web-ui-oyt" "just run-agent-sdk-user-web-ui-oyt"
  start_service "agent-sdk-user-web-ui-ua" "just run-agent-sdk-user-web-ui-ua"
  start_service "agent-sdk-provider-web-ui-oyt" "just run-agent-sdk-provider-web-ui-oyt"
  start_service "agent-sdk-provider-web-ui-ua" "just run-agent-sdk-provider-web-ui-ua"
  #
  # List all running tmux sessions
  echo -e "\n${GREEN}All running services:${NC}"
  tmux list-sessions
  #
  echo -e "\n${BLUE}Usage:${NC}"
  echo "- View a service: tmux attach -t service-name"
  echo "- Kill a service: tmux kill-session -t service-name"
  echo "- Stop the demo: just stop-demo"
  echo -e "\n${BLUE}Web UI urls:${NC}"
  echo "untied-airlines-user-web-ui: http://localhost:5173"
  echo "agent-sdk-user-web-ui-oyt: http://localhost:5176"
  echo "agent-sdk-user-web-ui-ua: http://localhost:5177"
  echo "agent-sdk-provider-web-ui-oyt: http://localhost:5174"
  echo "agent-sdk-provider-web-ui-ua: http://localhost:5175"



stop-demo:
  #!/bin/sh
  set -eu
  echo "Terminating all tmux sessions and their processes..."
  
  # First, get the PIDs of processes running in tmux sessions
  for session in $(tmux list-sessions -F "#{session_name}" 2>/dev/null); do
      # Get the pane PIDs for this session
      pids=$(tmux list-panes -s -t "$session" -F "#{pane_pid}")
      
      for pid in $pids; do
          # Kill the process and its children
          echo "Killing process tree for PID $pid (session $session)"
          pkill -TERM -P $pid 2>/dev/null || true
          kill -TERM $pid 2>/dev/null || true
      done
  done

  echo "All sessions and processes terminated."