package router

import (
	"context"
	"time"
)

// Route represents a route with start and end points
type Route struct {
	StartPoint  string
	EndPoint    string
	Duration    time.Duration
	Distance    float64
	Description string
}

// RouteRequest defines parameters for requesting a route
type RouteRequest struct {
	StartPoint string
	EndPoint   string
	// Additional parameters could be added here, like:
	// PreferHighways bool
	// AvoidTolls     bool
}

// Router interface defines methods for getting routes
type Router interface {
	// GetRoute returns a route between two points
	GetRoute(ctx context.Context, req RouteRequest) (Route, error)
}
