/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "config.h"
#include "GamepadManager.h"

#if ENABLE(GAMEPAD)

#include "Gamepad.h"
#include "GamepadStrategy.h"
#include "NavigatorGamepad.h"
#include "PlatformGamepad.h"
#include "PlatformStrategies.h"

namespace WebCore {

GamepadManager& GamepadManager::shared()
{
    static NeverDestroyed<GamepadManager> sharedManager;
    return sharedManager;
}

GamepadManager::GamepadManager()
{
    platformStrategies()->gamepadStrategy()->stopMonitoringGamepads(this);
}

void GamepadManager::platformGamepadConnected(unsigned index)
{
    for (auto& navigator : m_navigators)
        navigator->gamepadConnected(index);

    // FIXME: Fire connected event to all pages with listeners.
}

void GamepadManager::platformGamepadDisconnected(unsigned index)
{
    // FIXME: Fire disconnected event to all pages with listeners.

    for (auto& navigator : m_navigators)
        navigator->gamepadDisconnected(index);
}

void GamepadManager::registerNavigator(NavigatorGamepad* navigator)
{
    ASSERT(!m_navigators.contains(navigator));
    m_navigators.add(navigator);

    // FIXME: Monitoring gamepads will also be reliant on whether or not there are any
    // connected/disconnected event listeners.
    // Those event listeners will also need to register with the GamepadManager.
    if (m_navigators.size() == 1)
        platformStrategies()->gamepadStrategy()->startMonitoringGamepads(this);
}

void GamepadManager::unregisterNavigator(NavigatorGamepad* navigator)
{
    ASSERT(m_navigators.contains(navigator));
    m_navigators.remove(navigator);

    // FIXME: Monitoring gamepads will also be reliant on whether or not there are any
    // connected/disconnected event listeners.
    // Those event listeners will also need to register with the GamepadManager.
    if (m_navigators.isEmpty())
        platformStrategies()->gamepadStrategy()->stopMonitoringGamepads(this);
}

} // namespace WebCore

#endif // ENABLE(GAMEPAD)
