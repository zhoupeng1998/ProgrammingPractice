package router

import (
	"context"
	"fmt"
	"math/rand"
	"time"
)

// MockRouter is a mock implementation of the Router interface
type MockRouter struct {
	// Simulate delay in response time
	MinDelay time.Duration
	MaxDelay time.Duration
	// Simulate occasional errors
	ErrorRate float64
}

// NewMockRouter creates a new MockRouter with default settings
func NewMockRouter() *MockRouter {
	return &MockRouter{
		MinDelay:  100 * time.Millisecond,
		MaxDelay:  500 * time.Millisecond,
		ErrorRate: 0.1, // 10% chance of error
	}
}

// GetRoute implements the Router interface for mock testing
func (m *MockRouter) GetRoute(ctx context.Context, req RouteRequest) (Route, error) {
	// Simulate processing time
	delay := m.MinDelay + time.Duration(rand.Int63n(int64(m.MaxDelay-m.MinDelay)))

	select {
	case <-time.After(delay):
		// Continue processing
	case <-ctx.Done():
		return Route{}, ctx.Err()
	}

	// Simulate occasional errors
	if rand.Float64() < m.ErrorRate {
		return Route{}, fmt.Errorf("failed to get route from %s to %s: service unavailable",
			req.StartPoint, req.EndPoint)
	}

	// Generate a mock route
	distance := rand.Float64() * 100                     // Random distance between 0-100 km
	duration := time.Duration(distance*60) * time.Second // Rough estimate: 1 km per minute

	route := Route{
		StartPoint:  req.StartPoint,
		EndPoint:    req.EndPoint,
		Duration:    duration,
		Distance:    distance,
		Description: fmt.Sprintf("Route from %s to %s via mock path", req.StartPoint, req.EndPoint),
	}

	return route, nil
}
