#pragma once

#include "k3/logging/log.hpp"

#include "window.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include "pipeline.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace k3::graphics {
 
    class K3Renderer {

        public: 

            K3Renderer(std::shared_ptr<K3Window> window, std::shared_ptr<K3Device> device);

            ~K3Renderer();

            bool isFrameInProgress() const {return m_isFrameStarted; }

            //K3SwapChain getSwapChain() const {return *m_swapChain.get(); };

            uint32_t getSwapChainImageCount() const {
                return m_swapChain->imageCount();
            }

            VkRenderPass getSwapChainRenderPass() const {return m_swapChain->getRenderPass(); };

            float getAspectRatio() const { return m_swapChain->extentAspectRatio(); }

            VkCommandBuffer getCurrentCommandBuffer() const {
                assert(m_isFrameStarted && "Cannot get command buffer when frame not in progress");
                return m_commandBuffers[m_currentFrameIndex];
            };

            int getFrameIndex() const {
                assert(m_isFrameStarted && "Cannot get frame index when frame not in progress");
                return m_currentFrameIndex;    
            }

            VkCommandBuffer beginFrame();

            void endFrame();

            void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

            void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

        private: 

            void createCommandBuffers();

            void freeCommandBuffers();

            void recreateSwapChain();

            std::shared_ptr<K3Window> m_window;

            std::shared_ptr<K3Device> m_device;

            std::unique_ptr<K3SwapChain> m_swapChain;

            std::vector<VkCommandBuffer> m_commandBuffers;

            uint32_t m_currentImageIndex;

            int m_currentFrameIndex = 0;

            bool m_isFrameStarted = false;

    };

}