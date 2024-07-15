#!/bin/bash

# run mee admin services in separate tmux session
cd mee_user_manager
tmux new-session -s mee-network-admin-services -n mee-user-manager -d
tmux send-keys -t mee-network-admin-services:mee-user-manager 'make dev' C-m

cd ../mee_provider_manager
tmux new-window -t mee-network-admin-services -n mee-provider-manager
tmux send-keys -t mee-network-admin-services:mee-provider-manager 'make dev' C-m

cd ../mdn_license_manager
tmux new-window -t mee-network-admin-services -n mdn-license-manager
tmux send-keys -t mee-network-admin-services:mdn-license-manager 'make dev' C-m

cd ../oidc_provider
tmux new-window -t mee-network-admin-services -n mee-oidc-provider
tmux send-keys -t mee-network-admin-services:mee-oidc-provider 'make dev' C-m

tmux a
