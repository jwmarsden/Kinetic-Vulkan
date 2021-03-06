#pragma once

#include "k3/logging/log.hpp"

#include "device.hpp"

namespace k3::graphics {

    class K3SwapChain {

        public:

            static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

            K3SwapChain(std::shared_ptr<K3Device> deviceRef, VkExtent2D windowExtent);

            K3SwapChain(std::shared_ptr<K3Device> deviceRef, VkExtent2D windowExtent, std::unique_ptr<K3SwapChain> previous);

            ~K3SwapChain();

            VkFormat findDepthFormat();

            VkSwapchainKHR getSwapChain() {
                return m_swapChain;
            }

            VkRenderPass getRenderPass() { 
                return m_renderPass; 
            }

            VkImageView getImageView(int index) { 
                return m_swapChainImageViews[index]; 
            }

            size_t imageCount() { 
                return m_swapChainImages.size(); 
            }

            VkFormat getSwapChainImageFormat() { 
                return m_swapChainImageFormat; 
            }

            VkExtent2D getSwapChainExtent() { 
                return m_swapChainExtent; 
            }

            uint32_t width() { 
                return m_swapChainExtent.width; 
            }

            uint32_t height() { 
                return m_swapChainExtent.height; 
            }

            VkFramebuffer getFrameBuffer(int index) { 
                return m_swapChainFramebuffers[index]; 
            }

            float extentAspectRatio() {
                return static_cast<float>(m_swapChainExtent.width) / static_cast<float>(m_swapChainExtent.height);
            }

            VkResult acquireNextImage(uint32_t *imageIndex);

            VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

            bool compareSwapFormats(const K3SwapChain &swapChain) const {
                return swapChain.m_swapChainDepthFormat == m_swapChainDepthFormat && swapChain.m_swapChainImageFormat == m_swapChainImageFormat;
            }

        private:

            void initSystems();

            void createSwapChain();

            VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

            VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

            VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
            
            void createImageViews();

            void createRenderPass();

            void createDepthResources();

            void createFramebuffers();

            void createSyncObjects();

            std::shared_ptr<K3Device> m_device = nullptr;

            VkExtent2D m_windowExtent;

            VkSwapchainKHR m_swapChain = nullptr;

            std::shared_ptr<K3SwapChain> oldSwapChain = nullptr;
            
            std::vector<VkImage> m_swapChainImages;

            std::vector<VkImageView> m_swapChainImageViews;

            VkFormat m_swapChainImageFormat;
            
            VkFormat m_swapChainDepthFormat;

            VkExtent2D m_swapChainExtent;

            VkRenderPass m_renderPass;
            
            std::vector<VkImage> m_depthImages;

            std::vector<VkDeviceMemory> m_depthImageMemorys;

            std::vector<VkImageView> m_depthImageViews;

            std::vector<VkFramebuffer> m_swapChainFramebuffers;

            std::vector<VkSemaphore> m_imageAvailableSemaphores;

            std::vector<VkSemaphore> m_renderFinishedSemaphores;

            std::vector<VkFence> m_inFlightFences;

            std::vector<VkFence> m_imagesInFlight;

            size_t m_currentFrame = 0;

    };
}