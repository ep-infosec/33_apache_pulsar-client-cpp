/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <mutex>

namespace pulsar {

class MemoryLimitController {
   public:
    explicit MemoryLimitController(uint64_t memoryLimit);
    bool tryReserveMemory(uint64_t size);
    bool reserveMemory(uint64_t size);
    void releaseMemory(uint64_t size);
    uint64_t currentUsage() const;

    void close();

   private:
    const uint64_t memoryLimit_;
    std::atomic<uint64_t> currentUsage_;
    std::mutex mutex_;
    std::condition_variable condition_;
    bool isClosed_ = false;
};

}  // namespace pulsar
