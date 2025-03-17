# Alternative Route Service

This Go project demonstrates how to implement a service that provides alternative routes between two locations. It makes parallel calls to a routing service to gather multiple route options.

## Project Structure

- `router/`: Contains the router interface and a mock implementation
  - `router.go`: Defines the Router interface and route data structures
  - `mock_router.go`: Provides a mock implementation of the Router interface
- `service/`: Contains the alternative route service
  - `alternative_route.go`: Implements the GetAlternativeRoute functionality
- `cmd/main/`: Contains the main program for demonstration
  - `main.go`: Demonstrates how to use the alternative route service

## Features

- Concurrent processing of multiple route requests
- Configurable number of alternative routes to generate
- Support for different route variations (e.g., fastest, shortest, scenic)
- Timeout handling for route requests
- Rate limiting to prevent overloading the underlying router service

## Usage

To run the demo program:

```bash
go run cmd/main/main.go
```

## Example Implementation

The `AlternativeRouteService` demonstrates several important Go concurrency patterns:

1. Goroutines for parallel processing
2. Context for timeout and cancellation
3. Wait groups for synchronization
4. Mutex for protecting shared resources
5. Channels for collecting results from concurrent operations
6. Semaphores for limiting concurrency

## Mock Router

The mock router implementation simulates:

- Varying response times
- Occasional errors
- Realistic route calculation

This makes it suitable for testing the alternative route service without needing a real routing service.

## Real-World Usage

In a real-world application, you would:

1. Replace the mock router with a real routing service implementation
2. Add more sophisticated error handling and retry logic
3. Implement caching to improve performance
4. Add metrics and logging for monitoring 