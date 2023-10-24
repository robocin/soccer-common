#!/bin/bash

REPO_DOCKER_NAME="robocin/soccer-common"
REPO_DOCKER_TAG="latest"

docker build . -f Dockerfile -t ${REPO_DOCKER_NAME}:${REPO_DOCKER_TAG}

docker push ${REPO_DOCKER_NAME}:${REPO_DOCKER_TAG}